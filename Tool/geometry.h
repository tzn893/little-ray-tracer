#pragma once
#include <cmath>
#include <iostream>



#ifndef NUMBERIC_ERROR
#define NUMBERIC_ERROR(x) printf(x);exit(0); 
#endif 

#ifndef ESP
#define ESP 1e-4f
#endif

#ifndef MAX
#define MAX 1e10;
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const float EBP = 1e-4f;
const float PI = 3.1415f;

inline bool equalZero(float f) {
	return std::abs(f) < ESP;
}


template <class t> struct Vec2 {
	union {
		struct {t u, v;};
		struct {t x, y;};
		t raw[2];
	};
	Vec2() : u(0), v(0) {}
	Vec2(t _u, t _v) : u(_u),v(_v) {}
	inline Vec2<t> operator +(const Vec2<t> &V) const { return Vec2<t>(u+V.u, v+V.v); }
	inline Vec2<t> operator -(const Vec2<t> &V) const { return Vec2<t>(u-V.u, v-V.v); }
	inline Vec2<t> operator -()                 const { return Vec2<t>(-x, -y); }
	inline Vec2<t> operator *(float f)          const { return Vec2<t>(u*f, v*f); }
	inline t& operator[] (size_t i) { return raw[i]; }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vec2<t>& v);
};

template <class t> struct Vec3 {
	union {
		struct {t x, y, z;};
		struct { t ivert, iuv, inorm; };
		t raw[3];
	};
	Vec3() : x(0), y(0), z(0) {}
	Vec3(t _x, t _y, t _z) : x(_x),y(_y),z(_z) {}
	inline Vec3<t> operator ^(const Vec3<t> &v) const { return Vec3<t>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	inline Vec3<t> operator +(const Vec3<t> &v) const { return Vec3<t>(x+v.x, y+v.y, z+v.z); }
	inline Vec3<t> operator -(const Vec3<t> &v) const { return Vec3<t>(x-v.x, y-v.y, z-v.z); }
	inline Vec3<t> operator -()                 const { return Vec3<t>(-x, -y, -z); }
	inline Vec3<t> operator *(float f)          const { return Vec3<t>(x*f, y*f, z*f); }
	inline t       operator *(const Vec3<t> &v) const { return x*v.x + y*v.y + z*v.z; }
	inline Vec3<t>& operator =(const Vec3<t>& v) { x = v.x, y = v.y, z = v.z; return *this; }
	inline bool operator ==(const Vec3<t>& v) const { return x == v.x && y == v.y && z == v.z; }
	inline Vec3<t> operator /(const float f) const { return *this * (1 /f); }
	inline t& operator[] (size_t i) { return raw[i]; }
	float norm () const { return std::sqrt(x*x+y*y+z*z); }
	Vec3<t> & normalize(t l=1) { *this = (*this)*(l/norm()); return *this; }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vec3<t>& v);
};


template <class t> struct Vec4 {
	union {
		struct { t x, y, z,a; };
		struct { t ivert, iuv, inorm,ialpha; };
		t raw[4];
	};
	Vec4() : x(0), y(0), z(0),a(0) {}
	Vec4(t _x, t _y, t _z,t _a) : x(_x), y(_y), z(_z),a(_a) {}
	Vec4(const Vec4<t>& vec):x(vec.x), y(vec.y) , z(vec.z),a(vec.a) {}
	Vec4(const Vec3<t>& in) :x(in.x), y(in.y), z(in.z), a(1) {}
	//inline Vec4<t> operator ^(const Vec4<t>& v) const { return Vec4<t>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	Vec4& operator= (const Vec4& vec) { x = vec.x, y = vec.y, z = vec.z, a = vec.a; return *this; }
	inline Vec4<t> operator +(const Vec4<t>& v) const { return Vec4<t>(x + v.x, y + v.y, z + v.z,a + v.a); }
	inline Vec4<t> operator -(const Vec4<t>& v) const { return Vec4<t>(x - v.x, y - v.y, z - v.z,a - v.a); }
	inline Vec4<t> operator -()                 const { return Vec4<t>(-x, -y, -z, -a); }
	inline Vec4<t> operator *(float f)          const { return Vec4<t>(x * f, y * f, z * f,a * f); }
	inline t       operator *(const Vec4<t>& v) const { return x * v.x + y * v.y + z * v.z + a * v.a; }
	inline Vec4<t> operator /(float f)          const { return *this * (1 / f); }
	inline t& operator[] (size_t i) { return raw[i]; }
	inline Vec3<t> xyz()                        const { return Vec3<t>(x, y, z); }
	float norm() const { return std::sqrt(x * x + y * y + z * z + a * a); }
	Vec4<t>& normalize(t l = 1) { *this = (*this) * (l / norm()); return *this; }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vec4<t>& v);
};


template<class t> struct Matrix4x4 {
	union {
		struct {
			t a00, a01, a02, a03,
				a10, a11, a12, a13,
				a20, a21, a22, a23,
				a30, a31, a32, a33;
		};
		t raw[16];
		Vec4<t> row[4];
	};
	Matrix4x4() :raw{ 0 } {}
	Matrix4x4(const Vec4<t> vec[]) : row{vec[0],vec[1],vec[2],vec[3]} {}
	Matrix4x4(const t data[]) {
		memcpy(raw,data,sizeof(t) * 16);
	}
	Matrix4x4(t m00,t m01,t m02,t m03,
		t m10,t m11,t m12,t m13,
		t m20,t m21,t m22,t m23,
		t m30,t m31,t m32,t m33) {
		memcpy(raw,&m00,sizeof(t) * 16);
	}
	Matrix4x4(const Matrix4x4<t>& m) { this->Matrix4x4::Matrix4x4(m.raw); }
	Vec4<t> operator* (const Vec4<t>& vec) const{
		return Vec4<t>(row[0] * vec,
			           row[1] * vec,
			           row[2] * vec,
			           row[3] * vec);
	}
	Matrix4x4<t> T() const;

	Matrix4x4<t> R() const;

	Matrix4x4<t> operator* (const Matrix4x4<t>& m) const;

	Vec4<t>& operator[](size_t i) { return row[i]; }

	Matrix4x4<t>& operator=(const Matrix4x4<t>& m){
		memcpy(raw,m.raw,sizeof(t) * 16);
		return *this;
	}

	static const Matrix4x4<t> E;
};

template<class t>
Matrix4x4<t> const Matrix4x4<t>::E(\
   1 , 0 , 0 , 0,
   0 , 1 , 0 , 0,
   0 , 0 , 1 , 0,
   0 , 0 , 0 , 1
);

template<class t>
Matrix4x4<t> Matrix4x4<t>::operator*(const Matrix4x4<t>& m) const {
	Matrix4x4<t> Tm = m.T();
	Matrix4x4<t> result;
	for (int i = 0; i != 4; i++) {
		result.row[i] = (*this * Tm.row[i]);
	}
	return result.T();
}

template<class t>
Matrix4x4<t> Matrix4x4<t>::T() const {
	Matrix4x4<t> result;
	for (int i = 0; i != 16; i++) {
		int Ti = (i / 4 + i % 4) * 5 - i;
		result.raw[Ti] = raw[i];
	}
	return result;
}

template<class t>
Matrix4x4<t> Matrix4x4<t>::R() const {
	Matrix4x4 result = Matrix4x4::E;
	Matrix4x4 orgin = (*this);
	for (int l = 0; l != 4; l++) {
		if (equalZero(orgin[l][l])) {
			int i;
			for (i = l + 1; i < 4 && equalZero(orgin[i][l]); i++);
			if (i >= 4) { NUMBERIC_ERROR("the matrix is untraversable."); }
			orgin[l] = orgin[l] + orgin[i];
			result[l] = result[l] + result[i];
		}
		result[l] = result[l] / orgin[l][l];
		orgin[l] = orgin[l] / orgin[l][l];
		for (int i = 0; i != 4; i++) {
			if (i == l) continue;
			result[i] = result[i] + result[l] * (-orgin[i][l]);
			orgin[i] = orgin[i] + orgin[l] * (-orgin[i][l]);
		}
	}
	return result;
}

typedef Vec2<float> Vec2f;
typedef Vec2<int>   Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;
typedef Vec4<int>   Vec4i;
typedef Vec4<float> Vec4f;
typedef Matrix4x4<float> Matrix4x4f;

template<class t>
inline Vec3<t> cross(Vec3<t> v1,Vec3<t> v2) {
	return  Vec3<t>(
		v1.y * v2.z - v1.z * v2.y,
		v2.x * v1.z - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
		);
}

Matrix4x4f RotationM(const Vec3f& dirct,float a);
Matrix4x4f PositionM(const Vec3f& pos);
Matrix4x4f ScaleM(const Vec3f& scale);

Vec3i ftoi(Vec3f vec);


template <class t> std::ostream& operator<<(std::ostream& s, Vec2<t>& v) {
	s << "(" << v.x << ", " << v.y << ")";
	return s;
}

template <class t> std::ostream& operator<<(std::ostream& s, Vec3<t>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return s;
}

template <class t> std::ostream& operator<<(std::ostream& s,Vec4<t>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << "," << v.a << ")";
	return s;
}

template <class t> std::ostream& operator<<(std::ostream& s,Matrix4x4<t>& v) {
	for (int i = 0; i != 4;i++) {
		s << v.row[i] << std::endl;
	}
	return s;
}


float clamp(float f);
float clamp(float f,float max,float min);

template<typename Vec,size_t dim>
Vec clamp(Vec vec,float max,float min) {
	Vec result;
	for (int i = 0; i != dim; i++) {
		result[i] = vec[i] > min ? (vec[i] < max ? vec[i] : max) : min;
	}
	return result;
}


inline Vec2f clamp2f(Vec2f vec, float max, float min) {
	return clamp<Vec2f, 2>(vec, max, min);
}

inline Vec3f clamp3f(Vec3f vec, float max, float min) {
	return clamp<Vec3f, 3>(vec, max, min);
}

inline Vec4f clamp4f(Vec4f vec, float max, float min) {
	return clamp<Vec4f, 4>(vec, max, min);
}

bool solveX2(float a, float b, float c,float* x1,float* x2);


inline Vec3f transform(Matrix4x4f trans, Vec3f vec, int isVec) {
	Vec4f tvec = trans * Vec4f(vec.x, vec.y, vec.z, isVec);
	return Vec3f(tvec.x,tvec.y,tvec.z);
}