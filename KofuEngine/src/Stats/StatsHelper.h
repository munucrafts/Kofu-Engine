#pragma once
#include "vector"
#include <geometry/Mesh.h>

class StatsHelper
{
public:
	static StatsHelper& GetStatsHelper();
	int GetVertexCount(const std::vector<Mesh*> meshes);
	int GetIndexCount(const std::vector<Mesh*> meshes);
	int GetTriangleCount(const std::vector<Mesh*> meshes);
	int GetFPS();
	float GetDeltaMS();
	int GetDrawCallCount();
	void AppendDrawCallCount();
	void ClearDrawCallCount();

private:
	int drawCalls = 0;
	int FPS = 0;
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

