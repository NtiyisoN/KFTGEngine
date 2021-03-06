#ifndef KFTG_ASSET_MANAGER
#define KFTG_ASSET_MANAGER

#include "../types.hpp"
#include "../Module.hpp"
#include "../Singleton.hpp"
#include "../string.hpp"
#include "../map.hpp"
#include "../Asset/AssetTypes.hpp"
#include "Filesystem.hpp"

#define ASSET_TABLE_SIZE 2000

namespace KFTG
{

class AssetRegistry : public Singleton
{
public:
	static AssetRegistry* instance ();
	~AssetRegistry () {}

	void addAsset (const GUID &uid, void *asset, u32 size);
	void deleteAsset (GUID uid);
	void* queryAsset (const GUID &uid);

private:
	struct Element
	{
		Element () : asset (nullptr), size (0) {}
		Element (void *a, u32 s) : asset (a), size (s) {}
		Element (const Element &e) : asset (e.asset), size (e.size) {}
		void *asset;
		u32 size;
	};

	AssetRegistry () : _registry (false) {}

	map<Element> _registry;
};

class AssetLoader : public Singleton
{
public:
	static AssetLoader* instance ();
	~AssetLoader ();
	// no need to divide data into multiple files temporarily
	// only assets.data for all of serialized assets
	// and index.data for the data index in serialized xml
	void* loadAsset (const string &path);

private:
	AssetLoader ();

	AssetRegistry *_assetRegistry;
	Filesystem *_fs;
	XML *_index;
};

// May only be used by editor

class RawAssetLoader
{
public:
	RawAssetLoader ();
	~RawAssetLoader ();

private:
};

// May only be used by editor

class AssetPacker
{
public:
	AssetPacker ();
	~AssetPacker ();

private:
};

class AssetManager : public Module, public Singleton
{
public:
	static AssetManager* instance ();
	~AssetManager () {}
	virtual void init () override;
	virtual void exit () override;
	void* queryAsset (const string &guid);

private:
	AssetManager () {}

	AssetLoader *_assetLoader;
	AssetRegistry *_assetRegistry;
};

}

#endif // ASSET_MANAGER