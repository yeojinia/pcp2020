#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class RangeSlider : public QWidget
{
	Q_OBJECT

public:
	RangeSlider(QWidget* aParent = Q_NULLPTR);

	QSize minimumSizeHint() const override;

	float GetMinimun() const;
	void SetMinimum(float aMinimum);

	float GetMaximun() const;
	void SetMaximum(float aMaximum);

	float GetLowerValue() const;
	void SetLowerValue(float aLowerValue);

	float GetUpperValue() const;
	void SetUpperValue(float aUpperValue);

	void SetRange(float aMinimum, float aMaximum);

	QString GetFeatureName();
	void SetFeatureName(QString name);

protected:
	void paintEvent(QPaintEvent* aEvent) override;
	void mousePressEvent(QMouseEvent* aEvent) override;
	void mouseMoveEvent(QMouseEvent* aEvent) override;
	void mouseReleaseEvent(QMouseEvent* aEvent) override;
	void changeEvent(QEvent* aEvent) override;

	QRectF firstHandleRect() const;
	QRectF secondHandleRect() const;
	QRectF handleRect(int aValue) const;

signals:
	void lowerValueChanged(float aLowerValue);
	void upperValueChanged(float aUpperValue);
	void rangeChanged(float aMin, float aMax);

public slots:
	void setLowerValue(float aLowerValue);
	void setUpperValue(float aUpperValue);
	void setMinimum(float aMinimum);
	void setMaximum(float aMaximum);

private:
	Q_DISABLE_COPY(RangeSlider)
	float currentPercentage();
	float validWidth() const;

	float mMinimum;
	float mMaximum;
	float mLowerValue;
	float mUpperValue;
	bool mFirstHandlePressed;
	bool mSecondHandlePressed;
	float mInterval;
	float mDelta;
	QColor mBackgroudColorEnabled;
	QColor mBackgroudColorDisabled;
	QColor mBackgroudColor;
	QString mSliderName; // feature name
	
};


class SliderName : public QWidget
{
	Q_OBJECT

public:
	SliderName(QWidget* aParent = Q_NULLPTR);
protected:
	void paintEvent(QPaintEvent* aEvent) override;
};