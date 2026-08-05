#pragma once
#include <string>
#include <map>
#include <vector>

struct ResourceNode {
    std::string asset_name;
    std::string file_path;
    std::string asset_type; // "MODEL", "TEXTURE", "AUDIO"
    bool is_vram_cached;
};

class NayderAssetManagerRuntime {
private:
    std::map<std::string, ResourceNode> central_cache;
    int total_loaded_bytes = 0;

public:
    NayderAssetManagerRuntime();
    void LoadModel(const std::string& path);
    void LoadTexture(const std::string& path);
    void LoadSound(const std::string& path);
    void ExecuteResourceHotReload(); // v0.0.97 feature!
    void PrintStatistics();
};
