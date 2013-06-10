#include "waylandsurfacemodel.h"
#include <QWaylandSurface>

class WaylandSurfaceModelPrivate
{
friend class WaylandSurfaceModel;
    QList<QWaylandSurface *> items;
};

WaylandSurfaceModel::WaylandSurfaceModel(QObject *parent)
    : QAbstractListModel(parent)
    , d(new WaylandSurfaceModelPrivate)
{
}

WaylandSurfaceModel::~WaylandSurfaceModel()
{
    delete d;
}

int WaylandSurfaceModel::rowCount(const QModelIndex &) const
{
    return d->items.count();
}

QVariant WaylandSurfaceModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid())
        return QVariant();

    return QVariant::fromValue(d->items.at(index.row()));
}

bool WaylandSurfaceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid())
        return false;

    if (QWaylandSurface *surface = qobject_cast<QWaylandSurface *>(value.value<QObject *>())) {
        d->items.at(index.row())->deleteLater();
        d->items[index.row()] = surface;
        return true;
    }

    return false;
}
