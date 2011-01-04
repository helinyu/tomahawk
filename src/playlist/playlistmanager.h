#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QObject>
#include <QHash>
#include <QStackedWidget>

#include "collection.h"
#include "playlistinterface.h"

namespace Tomahawk {
class DynamicWidget;
}

class AnimatedSplitter;
class AlbumModel;
class AlbumView;
class CollectionModel;
class CollectionFlatModel;
class CollectionView;
class PlaylistModel;
class PlaylistView;
class QueueView;
class TrackProxyModel;
class TrackModel;
class TrackView;
class SourceInfoWidget;

class PlaylistManager : public QObject
{
Q_OBJECT

public:
    explicit PlaylistManager( QObject* parent = 0 );
    ~PlaylistManager();

    QWidget* widget() const { return m_widget; }
    PlaylistView* queue() const;

    bool isSuperCollectionVisible() const { return true; }

    bool show( const Tomahawk::playlist_ptr& playlist );
    bool show( const Tomahawk::dynplaylist_ptr& playlist );
    bool show( const Tomahawk::album_ptr& album );
    bool show( const Tomahawk::collection_ptr& collection );
    bool show( const Tomahawk::source_ptr& source );
    bool showSuperCollection();

    void showCurrentTrack();

signals:
    void numSourcesChanged( unsigned int sources );
    void numTracksChanged( unsigned int tracks );
    void numArtistsChanged( unsigned int artists );
    void numShownChanged( unsigned int shown );

    void repeatModeChanged( PlaylistInterface::RepeatMode mode );
    void shuffleModeChanged( bool enabled );

    void statsAvailable( bool b );
    void modesAvailable( bool b );

public slots:
    void setTreeMode();
    void setTableMode();
    void setAlbumMode();

    void showQueue();
    void hideQueue();

    void setFilter( const QString& filter );

    void setRepeatMode( PlaylistInterface::RepeatMode mode );
    void setShuffled( bool enabled );

private slots:
    void applyFilter();

private:
    void unlinkPlaylist();
    void linkPlaylist();

    QWidget* m_widget;
    QStackedWidget* m_stack;
    AnimatedSplitter* m_splitter;

    PlaylistModel* m_queueModel;
    QueueView* m_queueView;

    AlbumModel* m_superAlbumModel;
    AlbumView* m_superAlbumView;
    CollectionFlatModel* m_superCollectionFlatModel;
    CollectionView* m_superCollectionView;    
    PlaylistView* m_playlistView;
    
    QList<Tomahawk::playlist_ptr> m_loadedPlaylists;
    QList< Tomahawk::collection_ptr > m_superCollections;
    PlaylistModel* m_playlistModel;

    QHash< Tomahawk::dynplaylist_ptr, Tomahawk::DynamicWidget* > m_dynamicWidgets;
    QHash< Tomahawk::collection_ptr, CollectionView* > m_collectionViews;
    QHash< Tomahawk::collection_ptr, AlbumView* > m_collectionAlbumViews;
    QHash< Tomahawk::source_ptr, SourceInfoWidget* > m_sourceViews;

    PlaylistInterface* m_currentInterface;

    QWidget* m_currentInfoWidget;

    Tomahawk::collection_ptr m_currentCollection;

    int m_currentMode;
    bool m_superCollectionVisible;
    bool m_statsAvailable;
    bool m_modesAvailable;

    QTimer m_filterTimer;
    QString m_filter;
};

#endif // PLAYLISTMANAGER_H
