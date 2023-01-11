#pragma once
#include <core/declare.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace gui {

    class Package {
    private:
        std::string                                                 id_;
        std::string                                                 name_;
        std::string                                                 assetPath_;
        std::vector<PackageItem*>                                   packageItems_;

        std::unordered_map<std::string, PackageItem*>               itemsByID_;
        std::unordered_map<std::string, PackageItem*>               itemsByName_;
        // std::unordered_map<std::string, 
        std::string                                                 customID_;
        std::vector<std::string>                                    stringTable_;
        std::vector<std::unordered_map<std::string, std::string>>   dependencies_;
        std::vector<std::string>                                    branches_;
        int                                                         branchIndex_;
        // static data
        static std::unordered_map<std::string, Package*>            packageInstByID;
        static std::unordered_map<std::string, Package*>            packageInstByName;
        static std::vector<Package*>                                packageList_;
        static std::unordered_map<std::string, std::string>         vars_;
        static std::string                                          branch_;
        static Texture*                                             emptyTexture_;
    public:
        Package();
        ~Package();
        bool loadFromBuffer(ByteBuffer* byteBuffer);
    };

    Package* PackageForID(std::string const& id);
    Package* PackageForName(std::string const& name);
    Package* LoadPackageFromAsset(std::string const& assetPath);

}