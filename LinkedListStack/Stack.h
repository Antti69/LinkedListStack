#pragma once

template<typename T>
class Stacks
{
private:
	class Element
	{
	public:
		Element( T val,Element* pNext )
			:
			val( val ),
			pNext( pNext )
		{}
		Element( const Element& src )
			:
			val( src.val )
		{
			if( src.pNext != nullptr )
			{
				pNext = new Element( *src.pNext );
			}
		}
		Element& operator=( const Element& ) = delete;
		int GetVal() const
		{
			return val;
		}
		Element* Disconnect()
		{
			auto pTemp = pNext;
			pNext = nullptr;
			return pTemp;
		}
		int CountElements() const
		{
			if( pNext != nullptr )
			{
				return pNext->CountElements() + 1;
			}
			else
			{
				return 1;
			}
		}
		~Element()
		{
			delete pNext;
			pNext = nullptr;
		}

		T val;
		Element* pNext = nullptr;
	};
	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(Element* CurElement)
			:
			CurElement(CurElement)
		{}
		bool operator ==(Iterator& rhs)
		{
			return CurElement = rhs.CurElement;
		}
		bool operator !=(Iterator& rhs)
		{
			return CurElement != rhs.CurElement;
		}
		Iterator& operator ++()
		{
			CurElement = this->CurElement->pNext;
			return *this;
		}
		T& operator *()
		{
			return CurElement->val;
		}
	private:
		Element* CurElement = nullptr;
	};
	class ConstIterator
	{
	public:
		ConstIterator() = default;
		ConstIterator(Element* CurElement)
			:
			CurElement(CurElement)
		{}
		bool operator ==(ConstIterator& rhs)
		{
			return CurElement = rhs.CurElement;
		}
		bool operator !=(ConstIterator& rhs)
		{
			return CurElement != rhs.CurElement;
		}
		ConstIterator& operator ++()
		{
			CurElement = this->CurElement->pNext;
			return *this;
		}
		const T& operator *()
		{
			return CurElement->val;
		}
	private:
		Element* CurElement = nullptr;
	};

public:
	Stacks() = default;
	Stacks( const Stacks& src )
	{
		*this = src;
	}
	Stacks& operator=( const Stacks& src )
	{
		if( &src != this )
		{
			if( !Empty() )
			{
				delete pTop;
				pTop = nullptr;
			}

			if( !src.Empty() )
			{
				pTop = new Element( *src.pTop );
			}
		}
		return *this;
	}
	~Stacks()
	{
		delete pTop;
		pTop = nullptr;
	}
	void Push( int val )
	{
		pTop = new Element( val,pTop );
	}
	T Pop()
	{
		if( !Empty() )
		{
			const auto tempVal = pTop->GetVal();
			auto pOldTop = pTop;
			pTop = pTop->Disconnect();
			delete pOldTop;
			return tempVal;
		}
		else
		{
			return -1;
		}
	}
	int Size() const
	{
		if( !Empty() )
		{
			return pTop->CountElements();
		}
		else
		{
			return 0;
		}
	}
	bool Empty() const
	{
		return pTop == nullptr;
	}
	Iterator begin()
	{
		return pTop;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstIterator begin() const
	{
		return pTop;
	}
	ConstIterator end() const
	{
		return nullptr;
	}
private:
	Element* pTop = nullptr;
};

typedef Stacks<int> Stack;