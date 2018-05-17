#ifndef __URDE_CSCRIPTACTORKEYFRAME_HPP__
#define __URDE_CSCRIPTACTORKEYFRAME_HPP__

#include "CEntity.hpp"

namespace urde
{
class CScriptActorKeyframe : public CEntity
{
private:
    s32 x34_animationId;
    float x38_initialLifetime;
    float x3c_playbackRate;
    float x40_lifetime;
    union {
        struct
        {
            bool x44_24_looping : 1;
            bool x44_25_disableUpdate : 1;
            bool x44_26_fadeOut : 1;
            bool x44_27_timedLoop : 1;
            bool x44_28_playing : 1;
            bool x44_29_ : 1;
        };
        u8 _dummy = 0;
    };

public:
    CScriptActorKeyframe(TUniqueId uid, std::string_view name, const CEntityInfo& info, s32 animId,
                         bool looping, float lifetime, bool disableUpdate, u32 fadeOut, bool active,
                         float totalPlayback);

    void Accept(IVisitor& visitor);
    void AcceptScriptMsg(EScriptObjectMessage msg, TUniqueId objId, CStateManager& stateMgr);
    void Think(float, CStateManager&);
    void UpdateEntity(TUniqueId, CStateManager&);
};
}

#endif // __URDE_CSCRIPTACTORKEYFRAME_HPP__
