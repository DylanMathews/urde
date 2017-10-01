#include "CWorldShadowShader.hpp"

namespace urde
{

CWorldShadowShader::CWorldShadowShader(u32 w, u32 h)
: m_w(w), m_h(h) {}

void CWorldShadowShader::_buildTex(boo::IGraphicsDataFactory::Context& ctx)
{
    m_tex = ctx.newRenderTexture(m_w, m_h, boo::TextureClampMode::ClampToWhite, 1, 0);
}

void CWorldShadowShader::bindRenderTarget()
{
    CGraphics::g_BooMainCommandQueue->setRenderTarget(m_tex);
}

void CWorldShadowShader::drawBase(float extent)
{
    zeus::CVector3f verts[] = {{-extent, 0.f, extent}, {extent, 0.f, extent},
                               {-extent, 0.f, -extent}, {extent, 0.f, -extent}};
    m_vbo->load(verts, sizeof(zeus::CVector3f) * 4);

    m_uniform.m_matrix = CGraphics::GetPerspectiveProjectionMatrix(true) * CGraphics::g_GXModelView.toMatrix4f();
    m_uniform.m_color = zeus::CColor::skWhite;
    m_uniBuf->load(&m_uniform, sizeof(m_uniform));

    CGraphics::SetShaderDataBinding(m_zDataBind);
    CGraphics::DrawArray(0, 4);
}

void CWorldShadowShader::lightenShadow()
{
    m_uniform.m_color = zeus::CColor(1.f, 0.25f);
    m_uniBuf->load(&m_uniform, sizeof(m_uniform));

    CGraphics::SetShaderDataBinding(m_dataBind);
    CGraphics::DrawArray(0, 4);
}

void CWorldShadowShader::blendPreviousShadow()
{
    if (!m_prevQuad)
        m_prevQuad.emplace(EFilterType::Blend, m_tex);
    m_prevQuad->draw({1.f, 0.85f}, 1.f);
}

void CWorldShadowShader::resolveTexture()
{
    boo::SWindowRect rect = {0, 0, m_w, m_h};
    CGraphics::g_BooMainCommandQueue->resolveBindTexture(m_tex, rect, false, 0, true, false);
}

void CWorldShadowShader::Shutdown() {}

URDE_SPECIALIZE_SHADER(CWorldShadowShader)

}
