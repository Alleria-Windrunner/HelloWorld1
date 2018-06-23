#pragma once
auto sprite = Sprite::create("res/game/bar.png");   //创建进度框
sprite->setPosition(Point(size.width / 2, size.height - 20)); //设置框的位置
this->addChild(sprite);            //加到默认图层里面去
auto sprBlood = Sprite::create("res/game/blood.png");  //创建血条
ProgressTimer * progress = ProgressTimer::create(sprBlood); //创建progress对象
progress->setType(ProgressTimer::Type::BAR);        //类型：条状
progress->setPosition(Point(size.width / 2, size.height - 20));
//从右到左减少血量
progress->setMidpoint(Point(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
progress->setBarChangeRate(Point(1, 0));
progress->setTag(BLOOD_BAR);       //做一个标记
this->addChild(progress);
schedule(schedule_selector(GameScene::scheduleBlood), 0.1f);  //刷新函数，每隔0.1秒
void GameScene::scheduleBlood(float delta) {
	auto progress = (ProgressTimer *)this->getChildByTag(BLOOD_BAR);
	progress->setPercentage((((float)existLife) / PLAYER_LIFE) * 100);  //这里是百分制显示
	if (progress->getPercentage() < 0) {
		this->unschedule(schedule_selector(GameScene::scheduleBlood));
	}
}
