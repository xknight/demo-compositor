#ifndef WAYLANDSURFACEMODEL_H
#define WAYLANDSURFACEMODEL_H

#include <QAbstractListModel>

class WaylandSurfaceModelPrivate;

class WaylandSurfaceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WaylandSurfaceModel(QObject *parent = 0);
    ~WaylandSurfaceModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
    WaylandSurfaceModelPrivate *d;
};

#endif // WAYLANDSURFACEMODEL_H
