#pragma once
#include "core/base.h"
#include "math/struct/monoid.h"

template<Monoid Q,auto fupd,int xlo=0,int xhi=inf<signed>()> struct SegPersi{
	using T=decltype(Q::id());
	T v=Q::id();
	SegPersi *l{},*r{};
	~SegPersi(){/*double free?*/}

	SegPersi* upd(int i,T x,int cs=xlo,int ce=xhi){
		if(ce<=i or i+1<=cs) return this;
		if(i<=cs and ce<=i+1) return new SegPersi{fupd(v,x)};
		int cm=(cs+ce)/2;
		if(!l)l=new SegPersi;
		if(!r)r=new SegPersi;
		auto ret=new SegPersi;
		ret->l=l->upd(i,x,cs,cm);
		ret->r=r->upd(i,x,cm,ce);
		ret->v=Q::f(ret->l->v,ret->r->v);
		return ret;
	}
	T q(int s,int e, int cs=xlo, int ce=xhi){
		if(ce<=s or e<=cs)return Q::id();
		if(s<=cs and ce<=e) return v;
		int cm=(cs+ce)/2;
		if(!l)l=new SegPersi;
		if(!r)r=new SegPersi;
		return Q::f(l->q(s,e,cs,cm),r->q(s,e,cm,ce));
	}
};
//USAGE: boj.kr/14898
//USAGE: https://codeforces.com/contest/961/submission/100706299
