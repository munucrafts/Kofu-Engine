#include "StatsHelper.h"

StatsHelper& StatsHelper::GetStatsHelper()
{
	static StatsHelper instance;
	return instance;
}

unsigned int StatsHelper::GetTotalVertexCount(const std::vector<Mesh*> meshes)
{
	unsigned int count = 0;

	for (Mesh* mesh : meshes)
	{
		count = count + mesh->vertices.size();
	}

	return count;
}

unsigned int StatsHelper::GetTotalIndexCount(const std::vector<Mesh*> meshes)
{
	unsigned int count = 0;

	for (Mesh* mesh : meshes)
	{
		count = count + mesh->indices.size();
	}

	return count;
}

unsigned int StatsHelper::GetTotalTriangleCount(const std::vector<Mesh*> meshes)
{
	unsigned int count = 0;

	for (Mesh* mesh : meshes)
	{
		count = count + mesh->indices.size();
	}

	return count / 3;
}

unsigned int StatsHelper::GetFPS()
{
	return FPS;
}

float StatsHelper::GetDeltaMS()
{
	return deltaSecs * 1000.0f;
}

void StatsHelper::AppendDrawCallCount()
{
	drawCalls++;
}

void StatsHelper::ClearDrawCallCount()
{
	drawCalls = 0;
}

unsigned int StatsHelper::GetDrawCallCount()
{
	return drawCalls;
}

