#ifndef __DNACOMMON_MAPU_HPP__
#define __DNACOMMON_MAPU_HPP__

#include "DNACommon.hpp"

namespace DataSpec
{
namespace DNAMAPU
{
struct MAPU : BigDNA
{
    DECL_DNA
    Value<uint32_t> magic;
    Value<uint32_t> version;
    UniqueID32 hexMapa;
    Value<uint32_t> worldCount;
    struct Transform : BigDNA
    {
        DECL_DNA
        Value<atVec4f> xf[3];
    };
    struct World : BigDNA
    {
        DECL_DNA
        String<-1> name;
        UniqueID32 mlvl;
        Transform transform;
        Value<uint32_t> hexCount;
        Vector<Transform, DNA_COUNT(hexCount)> hexTransforms;
        DNAColor hexColor;
    };
    Vector<World, DNA_COUNT(worldCount)> worlds;

    static bool Cook(const hecl::BlenderConnection::DataStream::MapUniverse& mapu, const hecl::ProjectPath& out);
};

template <typename PAKRouter>
bool ReadMAPUToBlender(hecl::BlenderConnection& conn,
                       const MAPU& mapu,
                       const hecl::ProjectPath& outPath,
                       PAKRouter& pakRouter,
                       const typename PAKRouter::EntryType& entry,
                       bool force);

}
}

#endif // __DNACOMMON_MAPU_HPP__