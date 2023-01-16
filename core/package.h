#pragma once
#include <core/declare.h>
#include <string>
#include <unordered_map>
#include <vector>
//
#include <lightweight_comm.h>

namespace gui {

    class Package {
        struct dependence_t {
            std::string id;
            std::string name;
        };
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
        std::vector<dependence_t>                                   dependencies_;
        std::vector<std::string>                                    branches_;
        int                                                         branchIndex_;
        // static data
        static std::unordered_map<std::string, Package*>            packageInstByID;
        static std::unordered_map<std::string, Package*>            packageInstByName;
        static std::vector<Package*>                                packageList_;
        static std::unordered_map<std::string, std::string>         vars_;
        static std::string                                          branch_;
        static Texture*                                             emptyTexture_;
        static uint32_t                                             moduleInited_;
        static comm::IArchive*                                      archive_;
    public:
        Package();
        ~Package();
        bool loadFromBuffer(ByteBuffer* byteBuffer);
    private:
        static bool CheckModuleInitialized();
    public:
        static Package* AddPackage(std::string const& assetPath);
        static void InitPackageModule(comm::IArchive* archive);
    };

    Package* PackageForID(std::string const& id);
    Package* PackageForName(std::string const& name);
    Package* LoadPackageFromAsset(std::string const& assetPath);

}