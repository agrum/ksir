#ifndef KPRC_H
#define KPRC_H

#include <assert.h>

#include <QMutex>

template<class T> class kPRC
{
protected:
	T* m_obj;
	int* m_refcount;
	QMutex* m_mutex;

public:
	kPRC();
	kPRC(T* p_obj);
	kPRC(const kPRC& p_prc);
	~kPRC();
	kPRC& operator = (const kPRC& p_prc);

	int refCount() const;

	T* operator -> ();
	const T* operator -> () const;

	operator T*();
	operator const T*() const;

	operator kPRC<const T> () const;

	template <class U> operator kPRC<U> ();
	template <class U> friend class kPRC;

	template <class T> friend
		kPRC<T> const_ptr_cast(const kPRC<const T>& pPtrToCast);
	template <class T> friend
		kPRC<T> const_ptr_cast(const kPRC<T>& pPtrToCast);

private:
	void addRef();
	void release();
	bool empty() const;
};

/////////////////////////////////////////////////////

template<class T> inline
kPRC<T>::kPRC() :
	m_obj(NULL),
	m_refcount(NULL),
	m_mutex(NULL)
{

}

template<class T> inline
kPRC<T>::kPRC(T* p_obj) :
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
kPRC<T>::kPRC(const kPRC<T>& p_prc):
	m_obj(p_prc.m_obj),
	m_refcount(p_prc.m_refcount),
	m_mutex(p_prc.m_mutex)
{
	if(!p_prc.m_obj)
		return;

	addRef();
}

template<class T> inline
kPRC<T>::~kPRC()
{
	release();
}

template<class T> inline
kPRC<T>&
kPRC<T>::operator = (const kPRC<T>& p_prc)
{
	if(m_refcount == p_prc.m_refcount)
		return;

	release();

	if(!p_prc.m_obj)
		return;

	m_obj = p_prc.m_obj;
	m_refcount = p_prc.m_refcount;
	m_mutex = p_prc.m_mutex;

	addRef();

	return *this;
}

template<class _Tp> inline void kPRC<_Tp>::addRef()
{
	if(!m_mutex)
		return;

	//Increment counter
	m_mutex->lock();
		if(m_refcount)
			++(*m_refcount);
	m_mutex->lock();
}

template<class T> inline void kPRC<T>::release()
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
kPRC<T>::empty() const
{
	return m_obj == NULL;
}

template<class T> inline
int
kPRC<T>::getRefCount() const
{
	if(m_refcount)
		return *m_refcount;
	else
		return 0;
}

template<class T> inline
T*
kPRC<T>::operator -> ()
{
	return obj;
}

template<class T> inline
const T*
kPRC<T>::operator -> () const
{
	return obj;
}

template<class T> inline

kPRC<T>::operator T* ()
{
	return obj;
}

template<class T> inline

kPRC<T>::operator const T*() const
{
	return obj;
}

template<class T> inline

kPRC<T>::operator kPRC<const T>() const
{
	kPRC<const T> rtn;

	rtn.m_obj = m_obj;
	rtn.m_refcount = m_refcount;
	rtn.m_mutex = m_mutex;
	rtn.addRef();

	return rtn;
}

template<class T> template <class U> inline

kPRC<T>::operator kPRC<U>()
{
	kPRC<U> rtn;

	rtn.m_obj = static_cast<U*> (m_obj);
	rtn.m_refcount = m_refcount;
	rtn.m_mutex = m_mutex;
	rtn.addref();

	return rtn;
}

template <class T> inline
kPRC<T>
const_ptr_cast(const kPRC<const T>& pPtrToCast)
{
	kPRC<T> rtn;

	rtn.m_obj = const_cast<T*> (pPtrToCast.m_obj);
	rtn.m_refcount = pPtrToCast.m_refcount;
	rtn.m_mutex = pPtrToCast.m_mutex;
	rtn.addref();

	return rtn;
}

template <class T> inline
kPRC<T>
const_ptr_cast(const kPRC<T>& pPtrToCast)
{
	return pPtrToCast;
}

#endif // KPRC_H
