#include "Shop.h"
#include <fstream>
#include "Node.h"
#include "Inventory.h"
#include "Line.h"
#include "ItemSelector.h"

std::istream& operator >> (std::istream& is, NodeData& data)
{
	size_t req_size, build_size;
	std::string name;

	is >> data.page >> data.id >> data.row >> data.col >> data.price
		>> req_size >> build_size;
	for (size_t i=0; i<req_size; i++) { is >> name; data.req.push_back(name); }
	for (size_t i=0; i<build_size; i++) { is >> name; data.build.push_back(name); }
	return is;
}

std::istream& operator >> (std::istream& is, ItemData& data)
{
	is >> data.id >> data.full_name >> data.atk >> data.mag>> data.hp >> data.range
		>> data.wind >> data.atkSpd >> data.price;
	return is;
}

Shop::Shop()
{
	mPage = 1;
	ReadItemFile();
	ReadNodeFile();
	mpSelector = new ItemSelector();
	mTree.begin()->second->SetEnable(true);
}

void Shop::ReadItemFile()
{
	std::ifstream file;
    std::string filename = "item.dat";
	filename.insert(0, "Script/");
    file.open(filename.c_str(), std::ios_base::in);

    if (!file.is_open()) {
        printf("***Error: opening file: %s ***\n", filename);
        return; }

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

    if (!file.is_open()) {
        printf("***Error: opening file: %s ***\n", filename);
        return; }

    while (!file.eof())
    {
		NodeData data;
		file >> data;
		mTree.insert(std::make_pair(std::make_pair(data.page, data.id), new Node(data, mItems.find(data.id)->second)));
    }
    file.close();
}

bool Shop::CanPurchase(std::string id) 
{
	/*
	Node* it = &FindItem(id);
	int total_cost = it->GetPrice();
	int tally = 0;
	std::vector<std::string> req_items = it->GetRequirements();
	std::map<int ,ItemDetail*> inv_items = Inventory::Items();
	for (auto iv = inv_items.begin(); iv != inv_items.end(); iv++)
	{
		if (std::find(req_items.begin(), req_items.end(), iv->second->GetName()) == req_items.end()) 
			tally += iv->second->GetPrice();
	}
	if (total_cost <= tally) return true;
	else return false;
	*/
	return false;
}

std::vector<Node*> Shop::GetBranches(std::vector<std::string> builds)
{
	std::vector<Node*> temp;
	for (auto it = mTree.begin(); it != mTree.end(); ++it)
	{
		if (std::find(builds.begin(), builds.end(), it->second->ItemName()) != builds.end())
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
	
void Shop::Purchase(std::string id)
{
	auto it = mTree.find(std::make_pair(mPage, id));
	//it->Grow(id);
	//Inventory::Instance()->AddItem(it);
}

void Shop::BranchTo(std::string id)
{
	if (id == "") return;
	Node& start = FindItem(id);
	Point bottom = start.GetPoint();
	bottom.x = bottom.x + 48/2;
	bottom.y = bottom.y + 48;
	std::vector<Node*>& builds = GetBranches(start.GetBuilds());
	std::vector<Line*> paths;
	paths.push_back(new Line(bottom, 0));
	bottom.y += 24;
	Point lefting = bottom;
	Point righting = bottom;
	bool direction;
	for (auto it = builds.begin(); it != builds.end(); ++it)
	{
		(*it)->SetEnable(true);
		int left = (int)(*it)->GetTPoint().x - (int)start.GetTPoint().x;
		for (int i=0; i<left*2; ++i) 
		{
			direction = true;
			lefting.x += -24;
			paths.push_back(new Line(lefting, 1));
		}
		int right = (int)start.GetTPoint().x - (int)(*it)->GetTPoint().x;
		for (int i=0; i<right*2; ++i) 
		{ 
			direction = false;
			paths.push_back(new Line(righting, 1));
			righting.x += 24;
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
	if (p.x + 48 > mHover.x  && 
    p.x < mHover.x + 5  && 
    p.y + 48 > mHover.y && 
    p.y < mHover.y + 5)
    { 
		return true;
	}
	return false;
}

void Shop::KeyInput(const KeyStruct& rKeys)
{
	mHover = Point(rKeys.mouse_x, rKeys.mouse_y);
}

void Shop::Update(Uint32 deltaTicks)
{
	mpSelector->Reset();
	for (auto it = mTree.begin(); it != mTree.end(); it++) 
	{
		if (IsCollision(it->second->GetPoint()))
			mpSelector->MoveSelector(*it->second, FindDetail(it->second->ItemName()));
			it->second->SetEnable(true);
			BranchTo(mpSelector->Branch());
	}
}

void Shop::Draw(SDL_Surface *pDest)
{
	for (auto it = mTree.begin(); it != mTree.end(); it++)
		it->second->Draw(pDest);
	mpSelector->Draw(pDest);
}


