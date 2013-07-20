#include "Shop.h"
#include <vector>
#include <fstream>
#include "Node.h"
#include "Inventory.h"

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
	is >> data.id >> data.atk >> data.mag>> data.hp >> data.range
		>> data.wind >> data.atkSpd >> data.price;
	return is;
}

Shop::Shop()
{
	mPage = 1;
	ReadItemFile();
	ReadNodeFile();
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
}

Node& Shop::FindItem(std::string id)
{
	auto temp = mTree.find(std::make_pair(mPage, id));
	return *temp->second;
}
	
void Shop::Purchase(std::string id)
{
	auto it = mTree.find(std::make_pair(mPage, id));
	//it->Grow(id);
	//Inventory::Instance()->AddItem(it);
}

void Shop::KeyInput(const KeyStruct& rKeys)
{

}

void Shop::Update(Uint32 deltaTicks)
{
	
}

void Shop::Draw(SDL_Surface *pDest)
{
	for (auto it = mTree.begin(); it != mTree.end(); it++)
		it->second->Draw(pDest);
}


