#ifndef KPRC_H
#define KPRC_H

#include <assert.h>

#include <QMutex>

namespace ksir {

template<class T> class PRC
{

public:
	PRC();
	PRC(T* p_obj);
	PRC(const PRC& p_prc);
	~PRC();
	PRC& operator = (const PRC& p_prc);

	int refCount() const;

	T* operator -> ();
	const T* operator -> () const;

	operator T*();
	operator const T*() const;

	operator PRC<const T> () const;

	template <class U> operator PRC<U> ();
	template <class U> friend class PRC;

	template <class U> friend
		PRC<U> const_ptr_cast(const PRC<const U>& pPtrToCast);
	template <class U> friend
		PRC<U> const_ptr_cast(const PRC<U>& pPtrToCast);

private:
	void addRef();
	void release();
	bool empty() const;

protected:
	T* m_obj;
	int* m_refcount;
	QMutex* m_mutex;
};

}

/////////////////////////////////////////////////////
///
using namespace ksir;

template<class T> inline
PRC<T>::PRC() :
	m_obj(NULL),
	m_refcount(NULL),
	m_mutex(NULL)
{

}

template<class T> inline
PRC<T>::PRC(T* p_obj) :
	m_obj(p_obj),
	m_refcount(NULL),
	m_mutex(NULL)
{
	if(m_obj)
	{
		m_refcount = new int(1);
		m_mutex = new QMutex;
	}
}

template<class T> inline
PRC<T>::PRC(const PRC<T>& p_prc):
	m_obj(p_prc.m_obj),
	m_refcount(p_prc.m_refcount),
	m_mutex(p_prc.m_mutex)
{
	if(!p_prc.m_obj)
		return;

	addRef();
}

template<class T> inline
PRC<T>::~PRC()
{
	release();
}

template<class T> inline
PRC<T>&
PRC<T>::operator = (const PRC<T>& p_prc)
{
	if(m_refcount == p_prc.m_refcount)
		return *this;

	release();

	m_obj = p_prc.m_obj;
	m_refcount = p_prc.m_refcount;
	m_mutex = p_prc.m_mutex;

	addRef();

	return *this;
}

template<class _Tp> inline void PRC<_Tp>::addRef()
{
	if(!m_mutex)
		return;

	//Increment counter
	m_mutex->lock();
		if(m_refcount)
			++(*m_refcount);
	m_mutex->lock();
}

template<class T> inline void PRC<T>::release()
{
	if(!m_mutex)
		return;

	//Decrement counter
	m_mutex->lock();
		if(m_refcount)
			--(*m_refcount);
	m_mutex->unlock();

	//If last remaining, delete everything
	if(*m_refcount == 0)
	{
		delete m_obj;
		m_obj = NULL;

		delete m_refcount;
		m_refcount = NULL;

		delete m_mutex;
		m_mutex = NULL;
	}
}

template<class T> inline
bool
PRC<T>::empty() const
{
	return m_obj == NULL;
}

template<class T> inline
int
PRC<T>::refCount() const
{
	int rtn = 0;

	m_mutex->lock();
		if(m_refcount)
			rtn = *m_refcount;
	m_mutex->unlock();

	return rtn;
}

template<class T> inline
T*
PRC<T>::operator -> ()
{
	return m_obj;
}

template<class T> inline
const T*
PRC<T>::operator -> () const
{
	return m_obj;
}

template<class T> inline

PRC<T>::operator T* ()
{
	return m_obj;
}

template<class T> inline

PRC<T>::operator const T*() const
{
	return m_obj;
}

template<class T> inline

PRC<T>::operator PRC<const T>() const
{
	PRC<const T> rtn;

	rtn.m_obj = m_obj;
	rtn.m_refcount = m_refcount;
	rtn.m_mutex = m_mutex;
	rtn.addRef();

	return rtn;
}

template<class T> template <class U> inline

PRC<T>::operator PRC<U>()
{
	PRC<U> rtn;

	rtn.m_obj = static_cast<U*> (m_obj);
	rtn.m_refcount = m_refcount;
	rtn.m_mutex = m_mutex;
	rtn.addref();

	return rtn;
}

template <class T> inline
PRC<T>
const_ptr_cast(const PRC<const T>& pPtrToCast)
{
	PRC<T> rtn;

	rtn.m_obj = const_cast<T*> (pPtrToCast.m_obj);
	rtn.m_refcount = pPtrToCast.m_refcount;
	rtn.m_mutex = pPtrToCast.m_mutex;
	rtn.addref();

	return rtn;
}

template <class T> inline
PRC<T>
const_ptr_cast(const PRC<T>& pPtrToCast)
{
	return pPtrToCast;
}

#endif // KPRC_H
