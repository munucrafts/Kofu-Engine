#pragma once
#include "vector"
#include <geometry/Mesh.h>

class StatsHelper
{
public:
	static StatsHelper& GetStatsHelper();
	unsigned int GetTotalVertexCount(const std::vector<Mesh*> meshes);
	unsigned int GetTotalIndexCount(const std::vector<Mesh*> meshes);
	unsigned int GetTotalTriangleCount(const std::vector<Mesh*> meshes);
	unsigned int GetFPS();
	unsigned int GetDrawCallCount();
	float GetDeltaMS();
	void AppendDrawCallCount();
	void ClearDrawCallCount();

private:
	unsigned int drawCalls = 0;
	unsigned int FPS = 0;
	float deltaSecs = 0.0f;

private:
	StatsHelper() = default;
	~StatsHelper() = default;
	StatsHelper(const StatsHelper& instance) = delete;
	void operator= (const StatsHelper& instance) = delete;

private:
	friend class Engine;
	friend class Scene;
};

