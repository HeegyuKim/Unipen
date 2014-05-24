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
			for(auto iter : m_LayerList)
				iter.second->Update(eTime) ;

			ProcessPopLayer() ;
		}
		
		void Scene::Render()
		{
			for(auto iter : m_LayerList)
				iter.second->Render() ;
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

			m_PopLayerList.push_back(PopLayer) ;
			return PopLayer->second ;
		}
		void Scene::ProcessPopLayer()
		{
			for(auto iter : m_PopLayerList)
				m_LayerList.erase(iter) ;

			m_PopLayerList.clear() ;
		}
}