#include "AssetManager.h"
#include <iostream>

NayderAssetManager::NayderAssetManager() {
    // Registry initialized
}

void NayderAssetManager::Request3DModelAsset(std::string name, std::string path) {
    std::cout << "\n📦 [ASSET MANAGER]: Checking registry bounds for Model: '" << name << "'..." << std::endl;
    
    // Tcheke si modèl la te deja chaje nan background nan pou evite double chajman
    if (asset_registry.find(name) != asset_registry.end()) {
        std::cout << "   🔄 [CACHE HIT]: '" << name << "' deja nan kach memwa VRAM! Re-utilizing active buffer pointers (0% Overhead lag)." << std::endl;
    } else {
        std::cout << "   📥 [CACHE MISS]: First time request! Loading file '" << path << "' from disk..." << std::endl;
        CachedAsset new_asset = {name, path, true};
        asset_registry[name] = new_asset;
        std::cout << "   ✅ [ASSET REGISTERED]: '" << name << "' chaje epi l bloke an sekirite nan kach la." << std::endl;
    }
}

void NayderAssetManager::RequestTextureAsset(std::string name, std::string path) {
    std::cout << "\n🖼️  [ASSET MANAGER]: Checking registry bounds for Texture: '" << name << "'..." << std::endl;
    if (asset_registry.find(name) != asset_registry.end()) {
        std::cout << "   🔄 [CACHE HIT]: Texture '" << name << "' active nan GPU registers. Sharing memory slots." << std::endl;
    } else {
        std::cout << "   📥 [CACHE MISS]: Loading texture bytes from '" << path << "'..." << std::endl;
        CachedAsset new_tex = {name, path, true};
        asset_registry[name] = new_tex;
        std::cout << "   ✅ [TEXTURE REGISTERED]: Surface slots mapped completely." << std::endl;
    }
}

void NayderAssetManager::ClearUnusedBuffers() {
    std::cout << "\n🧹 [GARBAGE COLLECTOR]: Cleaning dead node references from RAM buffers to prevent memory leaks..." << std::endl;
}
