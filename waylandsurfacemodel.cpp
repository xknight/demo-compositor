#include "waylandsurfacemodel.h"
#include <QWaylandSurface>

#include <QDebug>

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

bool WaylandSurfaceModel::insertRow(int row, const QModelIndex &parent)
{
    if (row < 0 || row > d->items.count())
        return false;

    beginInsertRows(QModelIndex(), row, row);
    d->items.insert(row, 0);
    endInsertRows();
    return true;
}

QVariant WaylandSurfaceModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid())
        return QVariant();

    return QVariant::fromValue(d->items.at(index.row()));
}

bool WaylandSurfaceModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !idx.isValid())
        return false;

    if (QWaylandSurface *surface = qobject_cast<QWaylandSurface *>(value.value<QObject *>())) {
        if (QWaylandSurface *oldSurface = d->items.at(idx.row()))
            oldSurface->deleteLater();

        d->items[idx.row()] = surface;
        emit dataChanged(index(idx.row()), index(idx.row()), QVector<int>() << Qt::DisplayRole);
        return true;
    }

    return false;
}

QList<QWaylandSurface *> WaylandSurfaceModel::items() const
{
    return d->items;
}
