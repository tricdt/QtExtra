#include "qtslidecontroller.h"
#include <QtCore/QTimeLine>
#include <QtGui/QPixmap>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWizard>
class QtSlideControllerPrivate {
public:
    QtSlideController* q_ptr;
    double opacity;
    int previousIndex;
    int slideDir;
    bool inversed;
    bool faded;

    QtSlideController::SlideEffects effectFlags;
    QWidget* widget;
    QTimeLine *timeLine;
    QPixmap frames[2];
    QPixmap backbuffer;
    QtSlideControllerPrivate(QtSlideController* q);

    QPointF slidePoint(const QRectF& rect, qreal value, int frame) const;
    int currentDirection() const;
    void renderFrame(int frame, qreal value, QPainter& painter) const;

    void zoomFrame(QTransform& transform, const QRectF & rect, qreal value, int frame) const;
    void rollFrame(QTransform& transform, const QRectF & rect, qreal value, int frame) const;
    void rotateFrame(QTransform& transform, const QRectF & rect, qreal value, int frame) const;
    void shearFrame(QTransform& transform, const QRectF & rect, qreal value, int frame) const;
};

QtSlideControllerPrivate::QtSlideControllerPrivate(QtSlideController *q) :
    q_ptr(q),
    opacity(0.0),
    previousIndex(0),
    slideDir(QtSlideController::SlideUp),
    inversed(false),
    faded(true),
    widget(Q_NULLPTR)
{
    timeLine = new QTimeLine(900, q_ptr);
    timeLine->setUpdateInterval(5);
}

QtSlideController::QtSlideController(QObject *parent) :
    QObject(parent), d(new QtSlideControllerPrivate(this))
{
    connect(d->timeLine, &QTimeLine::valueChanged, this, &QtSlideController::render);
    connect(d->timeLine, &QTimeLine::finished, this, &QtSlideController::onAnimationFinished);
}

QtSlideController::~QtSlideController()
{

}

void QtSlideController::setWidget(QStackedWidget *w)
{

}

void QtSlideController::setWidget(QWizard *w)
{
    if (d->widget)
    {
        disconnect(d->widget);
        d->widget->removeEventFilter(this);
    }
    if (w)
    {
        connect(w, &QWizard::currentIdChanged, this, &QtSlideController::onCurrentChange);
        d->widget = w;
        d->widget->installEventFilter(this);
    }
}

QWidget * QtSlideController::widget() const
{

    return d->widget;
}

void QtSlideController::setEffects(QtSlideController::SlideEffects flags)
{

    d->effectFlags = flags;
}

QtSlideController::SlideEffects QtSlideController::effects() const
{

    return d->effectFlags;
}

void QtSlideController::setSlideDirection(int dir)
{

    d->slideDir = dir;
}

int QtSlideController::slideDirection() const
{

    return d->slideDir;
}

void QtSlideController::setDuration(int ms)
{

    d->timeLine->setDuration(ms);
}

int QtSlideController::duration() const
{

    return d->timeLine->duration();
}

void QtSlideController::setFaded(bool on)
{

    d->faded = on;
}

bool QtSlideController::isFaded() const
{

    return d->faded;
}

QWidget * QtSlideController::currentWidget() const
{

    if (qobject_cast<QWizard*>(d->widget) != Q_NULLPTR)
        return (static_cast<QWizard*>(d->widget) ? static_cast<QWizard*>(d->widget)->currentPage() : Q_NULLPTR);
    else
        return (static_cast<QStackedWidget*>(d->widget) ? static_cast<QStackedWidget*>(d->widget)->currentWidget() : Q_NULLPTR);
}

QWidget * QtSlideController::widget(int id) const
{

    if (qobject_cast<QWizard*>(d->widget) != Q_NULLPTR)
        return (static_cast<QWizard*>(d->widget) ? static_cast<QWizard*>(d->widget)->page(id) : Q_NULLPTR);
    else
        return (static_cast<QStackedWidget*>(d->widget) ? static_cast<QStackedWidget*>(d->widget)->widget(id) : Q_NULLPTR);
}

int QtSlideController::currentIndex() const
{

    if (qobject_cast<QWizard*>(d->widget) != Q_NULLPTR)
        return (static_cast<QWizard*>(d->widget) ? static_cast<QWizard*>(d->widget)->currentId() : -1);
    else
        return (static_cast<QStackedWidget*>(d->widget) ? static_cast<QStackedWidget*>(d->widget)->currentIndex() : -1);
}

int QtSlideController::count() const
{

    if (qobject_cast<QWizard*>(d->widget) != Q_NULLPTR)
        return (static_cast<QWizard*>(d->widget)->pageIds().size());
    else
        return (static_cast<QStackedWidget*>(d->widget)->count());
}


void QtSlideController::onCurrentChange(int i)
{

}

void QtSlideController::onAnimationFinished()
{

}

void QtSlideController::render(qreal value)
{

}

bool QtSlideController::eventFilter(QObject *watched, QEvent *event)
{
    return false;
}


