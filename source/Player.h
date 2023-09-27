#pragma once

#include <SFML/Graphics.hpp>


class CollisionBox {
public:
	CollisionBox(const sf::Vector3f& size_) : m_size(size_) {}
	bool check_collision(const sf::Vector3f& where_center_) { return false; };
protected:
	sf::Vector3f m_size;
};


sf::Vector3f vec_mul_matrix(const sf::Vector3f& vec_, const std::vector<std::vector<float>>& matrix_) {
	if (matrix_.size() != 3 
		&& matrix_[0].size() != 3 && matrix_[1].size() != 3 && matrix_[2].size() != 3) { return { 0,0,0 }; }
	return {
		vec_.x * matrix_[0][0] + vec_.y * matrix_[0][1] + vec_.z * matrix_[0][2],
		vec_.x * matrix_[1][0] + vec_.y * matrix_[1][1] + vec_.z * matrix_[1][2],
		vec_.x * matrix_[2][0] + vec_.y * matrix_[2][1] + vec_.z * matrix_[2][2] };
}


sf::Vector3f rotate_vector_x(const sf::Vector3f& vec_, float angle_) {
	auto&& res = vec_mul_matrix(vec_, { {1, 0, 0}, 
		{0, std::cos(angle_), -std::sin(angle_)}, 
		{0, std::sin(angle_), std::cos(angle_)}});
	return (res == sf::Vector3f{}) ? vec_ : res;
}

sf::Vector3f rotate_vector_y(const sf::Vector3f& vec_, float angle_) {
	auto&& res = vec_mul_matrix(vec_, { {std::cos(angle_), 0, std::sin(angle_)},
		{0, 1, 0},
		{-std::sin(angle_), 0, std::cos(angle_)} });
	return (res == sf::Vector3f{}) ? vec_ : res;
}

sf::Vector3f rotate_vector_z(const sf::Vector3f& vec_, float angle_) {
	auto&& res = vec_mul_matrix(vec_, {{std::cos(angle_), -std::sin(angle_), 0},
		{std::sin(angle_), std::cos(angle_), 0},
		{0, 0, 1}, });
	return (res == sf::Vector3f{}) ? vec_ : res;
}


class EnemyBase {
public:
	EnemyBase(const sf::Vector3f& position_, const sf::Vector3f& look_at_,
		std::shared_ptr<CollisionBox> ptr_collision_box_)
		: m_position(position_), m_look_at(look_at_), m_ptr_collision_box(ptr_collision_box_) {
		init();
	}
	~EnemyBase() = default;

	sf::Vector3f getPosition() const { return m_position; }
	sf::Vector3f getLookAt() const { return m_look_at; }

	void setPosition(const sf::Vector3f& position_) {
		m_position = position_;
	}
	void setLookAt(const sf::Vector3f& look_at_) {
		m_look_at = look_at_;
	}
	void rotate(float x_angle_, float y_angle_, float z_angle_) {
		rotate_x(x_angle_);
		rotate_y(y_angle_);
		rotate_z(z_angle_);
	}
	void rotate_x(float x_angle_) {
		m_look_at = rotate_vector_x(m_look_at, x_angle_);
	}
	void rotate_y(float y_angle_) {
		m_look_at = rotate_vector_y(m_look_at, y_angle_);
	}
	void rotate_z(float z_angle_) {
		m_look_at = rotate_vector_z(m_look_at, z_angle_);
	}
protected:
	sf::Vector3f m_position;
	sf::Vector3f m_look_at;
	std::shared_ptr<CollisionBox> m_ptr_collision_box;

	virtual void init() {

	}
};


class Player : public EnemyBase {
public:
	Player(const sf::Vector3f& position_, const sf::Vector3f& look_at_,
		std::shared_ptr<CollisionBox> ptr_collision_box_)
		: EnemyBase(position_, look_at_, ptr_collision_box_) {}
};