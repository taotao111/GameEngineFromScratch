#pragma once
#include <vector>
#include <memory>
#include "GfxStructures.hpp"
#include "IRuntimeModule.hpp"
#include "IShaderManager.hpp"
#include "geommath.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Polyhedron.hpp"
#include "IDrawPass.hpp"

namespace My {
    class GraphicsManager : implements IRuntimeModule
    {
    public:
        virtual ~GraphicsManager() {}

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

        virtual void Clear();
        virtual void Draw();

        virtual void UseShaderProgram(const intptr_t shaderProgram);
        virtual void SetPerFrameConstants(const DrawFrameContext& context);
        virtual void DrawBatch(const DrawBatchContext& context);
        virtual void DrawBatchDepthOnly(const DrawBatchContext& context);

        virtual intptr_t GenerateCubeShadowMapArray(const uint32_t width, const uint32_t height, const uint32_t count);
        virtual intptr_t GenerateShadowMapArray(const uint32_t width, const uint32_t height, const uint32_t count);
        virtual void BeginShadowMap(const Light& light, const intptr_t shadowmap, const uint32_t width, const uint32_t height, const uint32_t layer_index);
        virtual void EndShadowMap(const intptr_t shadowmap, const uint32_t layer_index);
        virtual void SetShadowMaps(const Frame& frame);
        virtual void DestroyShadowMap(intptr_t& shadowmap);

        virtual void DrawSkyBox(const DrawFrameContext& context);

#ifdef DEBUG
        virtual void DrawPoint(const Point& point, const Vector3f& color);
        virtual void DrawPointSet(const PointSet& point_set, const Vector3f& color);
        virtual void DrawPointSet(const PointSet& point_set, const Matrix4X4f& trans, const Vector3f& color);
        virtual void DrawLine(const Point& from, const Point& to, const Vector3f &color);
        virtual void DrawLine(const PointList& vertices, const Vector3f &color);
        virtual void DrawLine(const PointList& vertices, const Matrix4X4f& trans, const Vector3f &color);
        virtual void DrawTriangle(const PointList& vertices, const Vector3f &color);
        virtual void DrawTriangle(const PointList& vertices, const Matrix4X4f& trans, const Vector3f &color);
        virtual void DrawTriangleStrip(const PointList& vertices, const Vector3f &color);
        virtual void DrawTextureOverlay(const intptr_t shadowmap, uint32_t layer_index, float vp_left, float vp_top, float vp_width, float vp_height);
        virtual void DrawCubeMapOverlay(const intptr_t cubemap, float vp_left, float vp_top, float vp_width, float vp_height);
        virtual void DrawCubeMapOverlay(const intptr_t cubemap, uint32_t layer_index, float vp_left, float vp_top, float vp_width, float vp_height);
        virtual void ClearDebugBuffers();

        void DrawEdgeList(const EdgeList& edges, const Vector3f& color);
        void DrawPolygon(const Face& face, const Vector3f& color);
        void DrawPolygon(const Face& face, const Matrix4X4f& trans, const Vector3f& color);
        void DrawPolyhydron(const Polyhedron& polyhedron, const Vector3f& color);
        void DrawPolyhydron(const Polyhedron& polyhedron, const Matrix4X4f& trans, const Vector3f& color);
        void DrawBox(const Vector3f& bbMin, const Vector3f& bbMax, const Vector3f& color);
#endif

    protected:
        virtual void InitializeBuffers(const Scene& scene);
        virtual void ClearBuffers();

        virtual void InitConstants();
        virtual void CalculateCameraMatrix();
        virtual void CalculateLights();
        virtual void UpdateConstants();

#ifdef DEBUG
        virtual void RenderDebugBuffers();
#endif

    protected:
        static const uint32_t           kFrameCount  = 2;
        static const uint32_t           kMaxSceneObjectCount  = 65535;
        static const uint32_t           kMaxTextureCount  = 2048;

        uint32_t                        m_nFrameIndex = 0;

        std::vector<Frame>  m_Frames;
        std::vector<std::shared_ptr<IDrawPass>> m_DrawPasses;
    };

    extern GraphicsManager* g_pGraphicsManager;
}

