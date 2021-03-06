#pragma once

//
// 迭代器的型别
//
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

//
// Traits就像一台“特性萃取机”，榨取各个迭代器的特性（对应的型别）
//

// List<string> -> __ListIterator
// Vector ->T*
template <class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer           Pointer;
	typedef typename Iterator::Reference         Reference;
};

template <class T>
struct IteratorTraits<T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef typename T       ValueType;
	typedef typename int     DifferenceType;
	typedef typename T*      Pointer;
	typedef typename T&      Reference;
};

template <class T>
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef typename T       ValueType;
	typedef typename int     DifferenceType;
	typedef typename const T*      Pointer;
	typedef typename const T&      Reference;
};

template <class InputIterator>
inline int __Distance(InputIterator first, InputIterator last, 
					  ForwardIteratorTag)
{
	size_t n = 0;
	while (first != last)
	{
		++n;
		++first;
	}

	return n;
}


template <class InputIterator>
inline int __Distance(InputIterator first, InputIterator last,
					  RandomAccessIteratorTag)
{
	return last - first;
}


// List::Iterator
// Vector::Iterator
template <class InputIterator>
inline int Distance(InputIterator first, InputIterator last)
{
	return __Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
}

/////////////////////////////////////////////////
// 反向迭代器
template <class Iterator>
class ReverseIterator 
{
public:
	typedef typename IteratorTraits<Iterator>::IteratorCategory IteratorCategory;
	typedef typename IteratorTraits<Iterator>::DifferenceType DifferenceType;
	typedef typename IteratorTraits<Iterator>::Pointer Pointer;
	typedef typename IteratorTraits<Iterator>::Reference Reference;
	typedef typename IteratorTraits<Iterator>::ValueType ValueType;
	typedef ReverseIterator<Iterator> Self;

	explicit ReverseIterator(Iterator it)
		:_current(it)
	{}

	Reference operator*()
	{
		//return *_current;
		Iterator tmp = _current;
		return *(--tmp);
	}

	Pointer operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		--_current;
		return *this;
	}

	Self& operator--()
	{
		++_current;
		return *this;
	}

	bool operator!=(const Self& s) const
	{
		return _current != s._current;
	}

protected:
	Iterator _current;
};


