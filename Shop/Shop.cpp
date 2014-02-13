/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#include "Shop.h"
#include <fstream>
#include "Engine/SpriteResource.h"
#include "Node.h"
#include "Inventory.h"
#include "Line.h"
#include "ItemSelector.h"
#include "UI/NSprite.h"
#include "ItemDetail.h"
#include "Inventory.h"

std::istream& operator >> (std::istream& is, NodeData& data)
{
	size_t req_size, build_size;
	std::string name;

	is >> data.page >> data.id >> data.row >> data.col >> data.price
		>> req_size >> build_size;

	for (size_t i = 0; i < req_size; i++)
	{ 
		is >> name;
		data.req.push_back(name);
	}
	for (size_t i = 0; i < build_size; i++)
	{ 
		is >> name;
		data.build.push_back(name);
	}
	return is;
}

std::istream& operator >> (std::istream& is, ItemProperty& data)
{
	is >> data.name >> data.value;
	return is;
}

std::istream& operator >> (std::istream& is, ItemData& data)
{
	size_t property_count;
	ItemProperty property;
	
	is >> data.id >> data.full_name >> data.price >> property_count;
	for (size_t i = 0; i < property_count; i++)
	{
		is >> property;
		data.properties.push_back(property);
	}
	return is;
}

Shop::Shop(Point& s, Point& e) : MAX_PAGES(3), mClick(false), mDClick(false)
{
	mPage = 1;
	ReadItemFile();
	ReadNodeFile();
	mpSelector = new ItemSelector();

	mpPageleft = new NSprite(s.x + 45, s.y + 45,
		&SpriteResource::RequestResource("Shop", "page_left"));
	mpPageright = new NSprite(e.x - 45, e.y + 45,
		&SpriteResource::RequestResource("Shop", "page_right"));

	FindItem("flamesword").SetEnable(true);
}

void Shop::ReadItemFile()
{
	std::ifstream file;
    std::string filename = "item.dat";
	filename.insert(0, "Script/");
    file.open(filename.c_str(), std::ios_base::in);

    if (!file.is_open())
	{
        printf("***Error: opening file: %s ***\n", filename);
        return;
	}

    while (!file.eof())
	{
		ItemData data;
		file >> data;
		mItems.insert(std::make_pair(data.id, new ItemDetail(data)));
    }
    file.close();
}

void Shop::ReadNodeFile()
{
	std::ifstream file;
    std::string filename = "shop.dat";
	filename.insert(0, "Script/");
    file.open(filename.c_str(), std::ios_base::in);

    if (!file.is_open())
	{
        printf("***Error: opening file: %s ***\n", filename);
        return;
	}

    while (!file.eof())
	{
		NodeData data;
		file >> data;
		mTree.insert(std::make_pair(std::make_pair(data.page, data.id),
			new Node(data, mItems.find(data.id)->second)));
    }
    file.close();
}

std::vector<Node*> Shop::GetBranches(std::vector<std::string> builds)
{
	std::vector<Node*> temp;
	for (auto it = mTree.begin(); it != mTree.end(); ++it) 
	{
		if (std::find(builds.begin(), builds.end(),
			it->second->ItemName()) != builds.end())
		{
			temp.push_back(it->second);
		}
	}
	return temp;
}

Node& Shop::FindItem(std::string id)
{
	auto temp = mTree.find(std::make_pair(mPage, id));
	return *temp->second;
}

ItemDetail& Shop::FindDetail(std::string id)
{
	auto temp = mItems.find(id);
	return *temp->second;
}

void Shop::BranchTo(std::string id)
{
	if (id == "") return;

	bool direction;
	Node& start = FindItem(id);

	if (start.HasBranched()) 
		return;

	Point bottom = start.GetPoint();
	bottom.x = bottom.x + 48 / 2;
	bottom.y = bottom.y + 48;
	std::vector<Node*>& builds = GetBranches(start.GetBuilds());
	std::vector<Line*> paths;
	paths.push_back(new Line(bottom, 0));
	bottom.y += 24;
	Point lefting = bottom;
	Point righting = bottom;
	

	for (auto it = builds.begin(); it != builds.end(); ++it)
	{
		(*it)->SetEnable(true);
		int left = (int)(*it)->GetTPoint().x - (int)start.GetTPoint().x;
		for (int i = 0; i < left * 2; ++i) //lefting
		{
			direction = true;
			lefting.x += -24;
			paths.push_back(new Line(lefting, 1));
		}

		int right = (int)start.GetTPoint().x - (int)(*it)->GetTPoint().x;
		for (int i = 0; i < right * 2; ++i) //righting
		{ 
			direction = false;
			paths.push_back(new Line(righting, 1));
			righting.x += 24; //first element is already right-aligned
		}

		if (direction)
			paths.push_back(new Line(lefting, 0));
		else
			paths.push_back(new Line(righting, 0));
	}
	start.SetPaths(paths);
}

bool Shop::IsCollision(Point& p)
{
	return (p.x + 48 > mHover.x  && 
		p.x < mHover.x + 5  && 
		p.y + 48 > mHover.y && 
		p.y < mHover.y + 5) ?
		true : false;
}

bool Shop::IsCollisionR(HitBox& p)
{
	return (p.rect.x + p.rect.w > mHover.x  && 
		p.rect.x < mHover.x + 10  && 
		p.rect.y + p.rect.h > mHover.y && 
		p.rect.y < mHover.y + 10) ?
		true : false;
}

int Shop::ItemCost(Node& n, int money) 
{
	int tally = 0;
	std::vector<std::string> req_items = n.GetRequirements();
	std::map<int ,ItemDetail*> inv_items = Inventory::Items();

	for (auto it = inv_items.begin(); it != inv_items.end(); it++)
	{
		if (std::find(req_items.begin(), req_items.end(),
			it->second->GetName()) == req_items.end()) 
				tally += it->second->GetPrice();
	}
	return tally;
}

void Shop::Purchase(Node& d)
{
	if (Inventory::SpendMoney(ItemCost(d, Inventory::GetMoney())))
	{
		//SFX::PlaySound(cha-ching);
		BranchTo(mpSelector->Branch());
	}
	else
		mpSelector->Insufficient();
}

void Shop::KeyInput(const SDL_Event& rEvent)
{
	mHover = Point(rEvent.motion.x, rEvent.motion.y);
	if (rEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if (!mClick && rEvent.button.button == SDL_BUTTON_LEFT) 
		{
			mClick = true;
			mClickTimer.Start();
		}
		else if (mClick && mClickTimer.GetTicks() < 200)
			mDClick = true;
		else 
		{ 
			mClickTimer.Start();
			mClick = false;
			mDClick = false;
		}
		if (rEvent.key.keysym.sym == SDLK_LEFT)
			ChangePage(-1);
		if (rEvent.key.keysym.sym == SDLK_RIGHT)
			ChangePage(1);
	}
}

void Shop::ChangePage(int dir)
{
	mClick = false;
	mPage += dir;
	mPage < 1 ? mPage = MAX_PAGES : 0;
	mPage > MAX_PAGES ? mPage = 1 : 0;
}

void Shop::Update(Uint32 delta_ticks)
{
	mpSelector->Reset();
	for (auto it = mTree.begin(); it != mTree.end(); it++) 
	{
		if (IsCollision(it->second->GetPoint()))
		{
			if (!it->second->IsEnabled())
				continue;

			mpSelector->MoveSelector(*it->second,
				FindDetail(it->second->ItemName()));

			if (it->second->IsClick()) 
				Purchase(*it->second);
			if (mDClick)
				it->second->Click(true);
		}
		else
			it->second->Click(false);
	}
	if (mClick)
	{
		if (IsCollisionR(mpPageleft->GetBounds())) ChangePage(-1);
		if (IsCollisionR(mpPageright->GetBounds())) ChangePage(1);
	}
}

void Shop::Draw(SDL_Surface *pdest)
{
	for (auto it = mTree.begin(); it != mTree.end(); it++)
		if (it->first.first == mPage)
			it->second->Draw(pdest);

	mpSelector->Draw(pdest);
	mpPageleft->Draw(pdest);
	mpPageright->Draw(pdest);
}


