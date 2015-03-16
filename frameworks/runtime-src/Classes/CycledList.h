#ifndef __Boids__CycledList__
#define __Boids__CycledList__

#include <vector>
#include <functional>

template <typename D>
class CycledListElement //�Ż���ʱ����ö�ʹ���ڴ����new
{
public:
	D d;
	CycledListElement<D>* next;
	CycledListElement(D _d, CycledListElement<D>* _next = nullptr) : d(_d), next(_next)
	{
	}
};

template <typename D>
class CycledList
{
public:
	CycledListElement<D>* ap; //�����(access point������ѭ���б��е�����һ��Ԫ�ء����㿪ʼ����ѭ������apֻҪ����ɾ�����ǲ��ᱻ�ı�ġ�
	CycledListElement<D>* tail; //��Ԫ�ض�����������档��ʵҲ��ap��ǰһ��

	CycledList() : ap(nullptr), tail(nullptr), _size(0) //��ʵֻ��ʼ��tail�͹��ˣ���Ϊ�˵��Ե�ʱ�����ԣ���apҲ��ʼ����
	{
	}

	virtual ~CycledList()
	{
		clear();
	}

	bool empty()
	{
		return tail == nullptr; //tailΪ��˵��û���κν��
	}

	void push_back(D d)
	{
		if (empty())
		{
			ap = new CycledListElement<D>(d);
			ap->next = ap;
			tail = ap;
		}
		else
		{
			tail->next = new CycledListElement<D>(d, ap);
			tail = tail->next;
		}
		_size++;
	}

	//��insert_after_this������롣���ر�����Ԫ�ص����ڽ��
	CycledListElement<D>* insert(const D d, CycledListElement<D>* insert_after_this)
	{
		insert_after_this->next = new CycledListElement<D>(d, insert_after_this->next);
		_size++;
		if (insert_after_this == tail)
		{
			tail = insert_after_this->next;
		}
		return insert_after_this->next;
	}

	//��[to_insert_begin, to_insert_end)���뵽insert_after_this֮�󡣷������һ��������Ԫ�ص����ڽ�㡣begin��end��ͬ��ʾ��һȦ��������ʲô�����塣��begin���ᱻ�ظ��壬����Ԫ��ֻ����һ��
	CycledListElement<D>* insert(CycledListElement<D>* to_insert_begin, CycledListElement<D>* to_insert_end, CycledListElement<D>* insert_after_this)
	{
		//�ƺ�������д��O(1)�ģ���Ϊ��������ֱ�ӽӵģ�����������Ҫͳ��size��O(1)�����ˣ��Ǿ�ֱ����ô���ɡ���
		for (CycledListElement<D>* to_insert = to_insert_begin;;)
		{
			insert_after_this = insert(to_insert->d, insert_after_this);
			to_insert = to_insert->next;
			if (to_insert == to_insert_end) break;
		}
		return insert_after_this;
	}

	//��(erase_prev, erase_end)�����������˶��ǿ����䡣
	//���ͨ��prev == endɾ��ֻʣһ����ȫɾ�Ļ��õ���clear
	void erase(CycledListElement<D>* erase_prev, CycledListElement<D>* erase_end, std::function<void(D)> do_something_before_erase = nullptr)
	{
		bool tail_erased = false, ap_erased = false;
		for (CycledListElement<D>* to_delete = erase_prev->next; to_delete != erase_end;)
		{
			if (to_delete == tail)
			{
				tail_erased = true;
			}
			else if (to_delete == ap)
			{
				ap_erased = true;
			}

			if (do_something_before_erase)
			{
				do_something_before_erase(to_delete->d);
			}

			CycledListElement<D>* next_bak = to_delete->next;
			delete to_delete;
			_size--;
			to_delete = next_bak;
		}
		erase_prev->next = erase_end;

		if (tail_erased)
		{
			tail = erase_prev;
		}
		if (ap_erased)
		{
			ap = erase_end;
		}
	}

	void clear(std::function<void(D)> do_something_before_erase = nullptr)
	{
		for (CycledListElement<D>* to_delete = ap;;)
		{
			if (do_something_before_erase)
			{
				do_something_before_erase(to_delete->d);
			}

			CycledListElement<D>* next_bak = to_delete->next;
			delete to_delete;
			to_delete = next_bak;
			if (to_delete == ap) break;
		}
		ap = tail = nullptr;
		_size = 0;
	}

	//����do_something�ĵ�һ������Ҫ��֤����ɾ��
	void foreachelement(std::function<void(CycledListElement<D>*)> do_something)
	{
		for (CycledListElement<D>* e = ap;;)
		{
			do_something(e);
			e = e->next;
			if (e == ap) break;
		}
	}

	//����do_something�ĵ�һ������Ҫ��֤����ɾ��
	void foreachelement2(std::function<void(CycledListElement<D>*, CycledListElement<D>*)> do_something)
	{
		for (CycledListElement<D>* e = ap;;)
		{
			do_something(e, e->next);
			e = e->next;
			if (e == ap) break;
		}
	}

	//����do_something�ĵ�һ������Ҫ��֤����ɾ��
	void foreachelement2_with_break(std::function<bool(CycledListElement<D>*, CycledListElement<D>*)> do_something)
	{
		for (CycledListElement<D>* e = ap;;)
		{
			if (do_something(e, e->next)) break;
			e = e->next;
			if (e == ap) break;
		}
	}

	void foreach(std::function<void(D)> do_something)
	{
		for (CycledListElement<D>* e = ap;;)
		{
			do_something(e->d);
			e = e->next;
			if (e == ap) break;
		}
	}

	void foreach_with_counter(std::function<void(D, int)> do_something)
	{
		int i = 0;
		for (CycledListElement<D>* e = ap;;)
		{
			do_something(e->d, i++);
			e = e->next;
			if (e == ap) break;
		}
	}

	void foreach2(std::function<void(D, D)> do_something)
	{
		for (CycledListElement<D>* e = ap;;)
		{
			do_something(e->d, e->next->d);
			e = e->next;
			if (e == ap) break;
		}
	}

	void foreach2_with_break(std::function<bool(D, D)> do_something)
	{
		for (CycledListElement<D>* e = ap;;)
		{
			if (do_something(e->d, e->next->d)) break;
			e = e->next;
			if (e == ap) break;
		}
	}

	void foreach3(std::function<void(D, D, D)> do_something)
	{
		for (CycledListElement<D>* e = ap;;)
		{
			do_something(e->d, e->next->d, e->next->next->d);
			e = e->next;
			if (e == ap) break;
		}
	}

	void foreachref(std::function<void(D&)> do_something)
	{
		for (CycledListElement<D>* e = ap;;)
		{
			do_something(e->d);
			e = e->next;
			if (e == ap) break;
		}
	}

	void reverse()
	{
		std::vector<CycledListElement<D>*> elements;
		elements.reserve(_size); 
		foreachelement([&](CycledListElement<D>* e)
		{
			elements.push_back(e);
		});

		for (unsigned int i = _size - 1; i > 0; --i)
		{
			elements[i]->next = elements[i - 1];
		}
		elements.front()->next = elements.back();
		ap = elements.back();
		tail = elements.front();
	}

	int size() const
	{
		return _size;
	}

protected:
	int _size;
};

class CycledListTest
{
public:
	static void run();
};

#endif