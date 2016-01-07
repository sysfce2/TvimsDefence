#include "Enemy.h"
#include <iostream>

Enemy::Enemy(Image &image,  Vector2f startPosition, Vector2i spriteObjectSize, String Name, int Health, float Speed)
:Entity(image, startPosition, spriteObjectSize, Name)
{
		sprite.setTextureRect(IntRect(0, spriteSize.y, spriteSize.x, spriteSize.y));//���� � ��������
		acceleration.x = Speed;//���� ��������.���� ������ ������ ���������
		health = Health;//��������
		deathAnimationTimer = 0;//������ ������ �������� ������
}

void Enemy::startAnimation(float &time){//��������
	sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), 0, spriteSize.x, spriteSize.y));//�������� ������
	if (health <= 0) {  // ��� �������� �������� ������
		deathAnimationTimer += time;
		if (name == "ZombieEnemy") {//��� ��������� � ����� ������ ������ ����� �����
			sprite.setTextureRect(IntRect(37 * int(getCurrentFrame(time)), spriteSize.y + 1, 37, spriteSize.y + 1));//�������� ������
		}
		if (name == "BearZombieEnemy") {//��� ��������� � ����� ������ ������ ����� �����
			sprite.setTextureRect(IntRect(spriteSize.x * int(getCurrentFrame(time)), spriteSize.y, spriteSize.x, spriteSize.y + 1));//�������� ������
		}
		if (deathAnimationTimer > 500) {
				life = false; deathAnimationTimer = 0;
		}//���������� �������� � ������� �����
	}
}

void Enemy::attackHome(Home & home){//����� ����
	if (getRect().intersects(home.getRect())) { 
		home.setDamage(); 
	} // ���� ����� ����������� � ����� , �� �������
}

void Enemy::update(float time, Home & home){//��������� ����� 
		position.x += acceleration.x*time;//���� ��������
		sprite.setPosition(position.x + spriteSize.x / 2, position.y + spriteSize.y / 2); //������ ������� ������� � ����� ��� ������
		startAnimation(time);//�������� ��������
		checkDeath(); // �������� �� ������
		attackHome(home);//����� ����
		checkCollisionWithHome(home);//�������� ������������ � �����
}