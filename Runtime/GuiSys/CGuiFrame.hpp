#ifndef __URDE_CGUIFRAME_HPP__
#define __URDE_CGUIFRAME_HPP__

#include "CGuiWidget.hpp"
#include "CGuiAutoRepeatData.hpp"
#include "CGuiPhysicalMsg.hpp"
#include "CGuiControllerInfo.hpp"
#include "CGuiLogicalEventTrigger.hpp"
#include "CGuiWidgetIdDB.hpp"

namespace urde
{
class CGuiSys;
class CLight;
class CGuiCamera;
class CGuiHeadWidget;
class CFinalInput;
class CGuiLight;

enum class EFrameTransitionOptions
{
    Zero
};

class CGuiFrameTransitionOptions
{
    EFrameTransitionOptions x0_opts;
    bool x4_ = true;
    float x8_ = 1.f;
    zeus::CVector3f xc_;
public:
    CGuiFrameTransitionOptions(EFrameTransitionOptions opts)
    : x0_opts(opts) {}
};

class CGuiFrameMessageMapNode
{
    CGuiLogicalEventTrigger x0_trigger;
public:
    CGuiFrameMessageMapNode(const CGuiPhysicalMsg& msg, int val)
    : x0_trigger(msg, val, false) {}
};

class CGuiFrame
{
public:
    enum class EFrameStates
    {
    };
private:
    bool x0_controllerStatus[4] = {};
    std::string x4_name;
    u32 x14_id;
    CGuiFrameTransitionOptions x1c_transitionOpts;
    u32 x34_ = 0;
    u32 x38_ = 0;
    CGuiSys& x3c_guiSys;
    u32 x40_ = 0;
    CGuiHeadWidget* x44_headWidget = nullptr;
    std::unique_ptr<CGuiWidget> x48_rootWidget;
    CGuiCamera* x4c_camera = nullptr;
    CGuiWidget* x50_background = nullptr;
    zeus::CQuaternion x54_;
    CGuiWidgetIdDB x64_idDB;
    std::unordered_map<u32, u32> x7c_;
    std::vector<u32> x90_;
    std::vector<CGuiLight*> xa0_lights;
    int xb0_a;
    int xb4_b;
    int xb8_c;
    bool xbc_24_flag1 : 1;
    bool xbd_flag2 = false;

public:
    CGuiFrame(u32 id, const std::string& name, CGuiSys& sys, int a, int b, int c);

    CGuiSys& GetGuiSys() {return x3c_guiSys;}

    CGuiLight* GetFrameLight(int idx) {return xa0_lights[idx];}
    CGuiWidget* FindWidget(const std::string& name) const;
    CGuiWidget* FindWidget(s16 id) const;
    void ResetControllerStatus();
    void SetControllerStatus(int idx, bool set) {x0_controllerStatus[idx] = set;}
    void SetFrameBackground(CGuiWidget* bg) {x50_background = bg;}
    void SetFrameCamera(CGuiCamera* camr) {x4c_camera = camr;}
    void SetHeadWidget(CGuiHeadWidget* hwig) {x44_headWidget = hwig;}
    void InterpretGUIControllerState(const CFinalInput& input,
        CGuiPhysicalMsg::PhysicalMap& state,
        char&, char&, char&, char&);
    void FindWidget2LogicalEventMap(u64);
    void FindLogicalEventList(u64, s16);
    void SendWidgetMessage(s16,
        std::list<std::unique_ptr<CGuiFrameMessageMapNode>>&,
        CGuiPhysicalMsg::PhysicalMap& state,
        CGuiControllerInfo::CGuiControllerStateInfo& csInfo);
    void ClearAllMessageMap();
    void SortDrawOrder();
    void EnableLights(u32) const;
    void DisableLights() const;
    void RemoveLight(CGuiLight* light);
    void AddLight(CGuiLight* light);
    bool GetIsFinishedLoading() const;
    void Touch() const;
    void ProcessControllerInput(const CFinalInput& input);

    void Update(float dt);
    void Draw(const CGuiWidgetDrawParms& parms) const;
    void Stop(const CGuiFrameTransitionOptions&, EFrameStates, bool);
    void Run(CGuiFrame*, const CGuiFrameTransitionOptions&, EFrameStates, bool);
    void Initialize();
    void LoadWidgetsInGame(CInputStream& in);

    CGuiWidgetIdDB& GetWidgetIdDB() {return x64_idDB;}

    static CGuiFrame* CreateFrame(u32, CGuiSys& sys, CInputStream& in);
    static std::string CreateFrameName(u32);
};

}

#endif // __URDE_CGUIFRAME_HPP__