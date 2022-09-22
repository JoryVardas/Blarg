#include "Global_Variables.h"
#include "World.h"
#include "Model_Rotate.h"
#include "Model_Scale.h"
#include "Model_Translate.h"

#ifndef __WORLD_TOOLS_H__
#define __WORLD_TOOLS_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void RotateWorld(World* world, float x, float y, float z)
				{
					for(int i = 0; i < world->GetNumberOfMeshs(); i++)
					{
						Model_Rotate(world->_Meshs[i].GetData(), x, y, z);
					};
				};
				static void RotateWorld(World* world, Point3D center, float x, float y, float z)
				{
					for(int i = 0; i < world->GetNumberOfMeshs(); i++)
					{
						Model_Rotate(world->_Meshs[i].GetData(), center, x, y, z);
					};
				};
				
				static void ScaleWorld(World* world, float x, float y, float z)
				{
					for(int i = 0; i < world->GetNumberOfMeshs(); i++)
					{
						Model_Scale(world->_Meshs[i].GetData(), Point3D(0, 0, 0), x, y, z);
					};
				};
				static void ScaleWorld(World* world, float factor)
				{
					for(int i = 0; i < world->GetNumberOfMeshs(); i++)
					{
						Model_Scale(world->_Meshs[i].GetData(), Point3D(0, 0, 0), factor);
					};
				};
				static void ScaleWorld(World* world, Point3D centerOfScale, float x, float y, float z)
				{
					for(int i = 0; i < world->GetNumberOfMeshs(); i++)
					{
						Model_Scale(world->_Meshs[i].GetData(), centerOfScale, x, y, z);
					};
				};
				static void ScaleWorld(World* world, Point3D centerOfScale, float factor)
				{
					for(int i = 0; i < world->GetNumberOfMeshs(); i++)
					{
						Model_Scale(world->_Meshs[i].GetData(), centerOfScale, factor);
					};
				};
				
				static void TranslateWorld(World* world, float x, float y, float z)
				{
					for(int i = 0; i < world->GetNumberOfMeshs(); i++)
					{
						Model_Translate(world->_Meshs[i].GetData(), x, y, z);
					};
				};
			};
		};
	};
};

#endif