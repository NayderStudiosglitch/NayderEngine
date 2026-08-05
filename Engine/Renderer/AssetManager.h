#pragma once
#include <string>
#include <map>

struct CachedAsset {
    std::string asset_id;
    std::string file_path;
    bool loaded_in_vram = false;
};

class NayderAssetManager {
private:
    std::map<std::string, CachedAsset> asset_registry;

public:
    NayderAssetManager();
    void Request3DModelAsset(std::string name, std::string path);
    void RequestTextureAsset(std::string name, std::string path);
    void ClearUnusedBuffers();
};
