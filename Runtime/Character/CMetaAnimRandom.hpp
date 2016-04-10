#ifndef __PSHAG_CMETAANIMRANDOM_HPP__
#define __PSHAG_CMETAANIMRANDOM_HPP__

#include "IMetaAnim.hpp"
#include "IOStreams.hpp"

namespace urde
{

class CMetaAnimRandom : public IMetaAnim
{
public:
    CMetaAnimRandom(CInputStream& in);
    EMetaAnimType GetType() const {return EMetaAnimType::Random;}

    std::shared_ptr<CAnimTreeNode> GetAnimationTree(const CAnimSysContext& animSys,
                                                    const CMetaAnimTreeBuildOrders& orders) const;
    void GetUniquePrimitives(std::set<CPrimitive>& primsOut) const;
    std::shared_ptr<CAnimTreeNode> VGetAnimationTree(const CAnimSysContext& animSys,
                                                     const CMetaAnimTreeBuildOrders& orders) const;
};

}

#endif // __PSHAG_CMETAANIMRANDOM_HPP__
