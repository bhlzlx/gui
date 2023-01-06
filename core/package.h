#pragma once
#include <core/declare.h>
#include <string>
#include <unordered_map>

namespace gui {

    class Package {
    private:
        std::string                     id_;
        std::string                     name_;
        std::string                     assetPath_;
        std::vector<PackageItem*>       packageItems_;

        std::unordered_map<std::string, PackageItem*> itemsByID_;
        std::unordered_map<std::string, PackageItem*> itemsByName_;
        // std::unordered_map<std::string, 
    public:
        Package();
        ~Package();
        void loadFromBuffer(ByteBuffer* byteBuffer);
    };

    Package* PackageForID(std::string const& id);
    Package* PackageForName(std::string const& name);
    Package* LoadPackageFromAsset(std::string const& assetPath);

}