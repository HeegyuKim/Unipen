#ifndef SCENE_H
#define SCENE_H
#include "Entity.h"
#include <map>

namespace unipen
{
	class Layer ;

	/**
	 *@brief 장면개념을 구현한 클래스
	 *여러개의 Layer를 관리한다.
	*/
	class Scene : public Entity
	{
	private:
		typedef std::map<std::string, Layer*> LAYERLIST ;
		LAYERLIST m_LayerList ;
	public:
		Scene(void) ;
		virtual ~Scene(void) ;

	public:
		/**
		 *@brief 갖고잇는 모든 Layer들의 Update함수를 호출해준다.
		 *@param eTime 이전의 Update로부터 현재의 Update까지 걸린 시간
		 */
		virtual void Update(float eTime) ;
		
		//!brief 갖고있는 모든 Layer들의 Render함수를 호출해준다.
		virtual void Render() ;

	private:
		/**
		 *@brief 레이어를 추가한다.
		 *@param _iNewLayer 새로운 레이어
		 *@param _iLayerName 새로운 레이어의 이름, 이는 찾거나 삭제할 때 쓰인다.
		 */
		void AddLayer(Layer* _iNewLayer, std::string _iLayerName) ;
		/**
		 *@brief 레이어 이름으로 레이어를 얻어온다.
		 *@param _iLayerName 얻어올 레이어의 이름
		 *@return 이름에 해당하는 레이어, 이름에 해당하는 레이어가 없다면 nullptr 리턴
		 */
		Layer* GetLayer(std::string _iLayerName) ;
		/**
		 *@brief 레이어 이름으로 레이어를 빼낸다.
		 *@param _iLayerName 빼낼 레이어의 이름
		 *@return 빼낸 레이어, 이름에 해당하는 레이어가 없다면 nullptr 리턴
		 */
		Layer* PopLayer(std::string _iLayerName) ;
	} ;
}

#endif