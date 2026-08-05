#pragma once
#include <string>
#include <vector>

struct PackagedAssetMetadata {
    std::string archive_relative_path;
    unsigned long raw_byte_size;
    unsigned long compressed_byte_size;
    std::string encryption_hash;
};

class NayderPackagingSystem {
private:
    std::vector<PackagedAssetMetadata> manifest_pool;
    std::string target_output_pak = "neonfall17_assets.pak";
    std::string shipping_executable = "NeonFall17.exe";

public:
    NayderPackagingSystem();
    void StageLooseAssetForPackaging(std::string path, unsigned long byte_size);
    void CompileStandaloneShippingBuild();
};
