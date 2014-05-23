#include "Scene.h"
#include "Layer.h"

namespace unipen
{
		Scene::Scene(void)
		{
		}
		Scene::~Scene(void)
		{
		}

		void Scene::Update(float eTime)
		{
			for(LAYERLIST::iterator iter = m_LayerList.begin(); iter != m_LayerList.end(); iter++)
				iter->second->Update(eTime) ;
		}
		
		void Scene::Render()
		{
			for(LAYERLIST::iterator iter = m_LayerList.begin(); iter != m_LayerList.end(); iter++)
				iter->second->Render() ;
		}

		void Scene::AddLayer(Layer* _iNewLayer, std::string _iLayerName)
		{
			m_LayerList[_iLayerName] = _iNewLayer ;
		}
		Layer* Scene::GetLayer(std::string _iLayerName)
		{
			LAYERLIST::iterator FindingLayer = m_LayerList.find(_iLayerName) ;
			if(FindingLayer == m_LayerList.end())
				return nullptr ;

			return FindingLayer->second ;
		}
		Layer* Scene::PopLayer(std::string _iLayerName)
		{
			LAYERLIST::iterator PopLayer = m_LayerList.find(_iLayerName) ;
			if(PopLayer == m_LayerList.end())
				return nullptr ;

			Layer* ReturnLayer = PopLayer->second ;
			m_LayerList.erase(PopLayer) ;

			return ReturnLayer ;
		}
}