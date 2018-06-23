#pragma once
auto sprite = Sprite::create("res/game/bar.png");   //�������ȿ�
sprite->setPosition(Point(size.width / 2, size.height - 20)); //���ÿ��λ��
this->addChild(sprite);            //�ӵ�Ĭ��ͼ������ȥ
auto sprBlood = Sprite::create("res/game/blood.png");  //����Ѫ��
ProgressTimer * progress = ProgressTimer::create(sprBlood); //����progress����
progress->setType(ProgressTimer::Type::BAR);        //���ͣ���״
progress->setPosition(Point(size.width / 2, size.height - 20));
//���ҵ������Ѫ��
progress->setMidpoint(Point(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
progress->setBarChangeRate(Point(1, 0));
progress->setTag(BLOOD_BAR);       //��һ�����
this->addChild(progress);
schedule(schedule_selector(GameScene::scheduleBlood), 0.1f);  //ˢ�º�����ÿ��0.1��
void GameScene::scheduleBlood(float delta) {
	auto progress = (ProgressTimer *)this->getChildByTag(BLOOD_BAR);
	progress->setPercentage((((float)existLife) / PLAYER_LIFE) * 100);  //�����ǰٷ�����ʾ
	if (progress->getPercentage() < 0) {
		this->unschedule(schedule_selector(GameScene::scheduleBlood));
	}
}
