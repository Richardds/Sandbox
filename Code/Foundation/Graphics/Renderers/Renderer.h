// ----------------------------------------------------------------------------------------
//  \file       Renderer.h
//  \author     Richard Boldiš <boldiric@fit.cvut.cz>
// ----------------------------------------------------------------------------------------

#pragma once

#include "Precompiled.h"
#include "Core/Debug.h"

namespace Graphics
{
	/// Base class of every renderer
	/// Holds shader class with which draws to buffers
	template <class T>
	class Renderer
	{
	public:
		enum class State
		{
			Initial,
			Ready
		};

		Renderer();

		[[nodiscard]] State GetState() const;
		[[nodiscard]] std::shared_ptr<T> GetShader() const;
		void FinishLoading();

	protected:
		std::shared_ptr<T> _shader;

	private:
		State _state;
	};

	template <class T>
	Renderer<T>::Renderer() :
		_state(State::Initial)
	{
	}

	template <class T>
	typename Renderer<T>::State Renderer<T>::GetState() const
	{
		return this->_state;
	}

	template <class T>
	std::shared_ptr<T> Renderer<T>::GetShader() const
	{
		return this->_shader;
	}

	template <class T>
	void Renderer<T>::FinishLoading()
	{
		_Assert(State::Initial == this->_state);
		this->_state = State::Ready;
	}
}
