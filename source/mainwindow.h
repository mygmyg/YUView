/*  YUView - YUV player with advanced analytics toolset
*   Copyright (C) 2015  Institut für Nachrichtentechnik
*                       RWTH Aachen University, GERMANY
*
*   YUView is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   YUView is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with YUView.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QList>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QMessageBox>
#include <QSettings>
#include <QTreeWidget>
#include <QMouseEvent>
#include <QTreeWidgetItem>
#include <QDesktopWidget>
#include <QKeyEvent>

#include "settingswindow.h"
#include "playlistTreeWidget.h"
#include "playlistItem.h"

typedef enum {
  WindowModeSingle,
  WindowModeSeparate
} WindowMode;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  bool eventFilter(QObject * target, QEvent * event);
  //void moveEvent ( QMoveEvent * event );
  void closeEvent(QCloseEvent *event);
  //void resizeEvent(QResizeEvent *event);

private:
  PlaylistTreeWidget *p_playlistWidget;
  Ui::MainWindow *ui;

  WindowMode p_windowMode;

  QMessageBox *p_msg;
  bool p_ClearFrame;

  QMenu* fileMenu;
  QMenu* viewMenu;
  QMenu* playbackMenu;
  QMenu* helpMenu;

public:
  void loadFiles(QStringList files) { p_playlistWidget->loadFiles( files ); }
  void loadPlaylistFile(QString filePath);

  bool isPlaylistItemSelected() { return selectedPrimaryPlaylistItem() != NULL; }

public slots:

  void enableSingleWindowMode();
  void enableSeparateWindowsMode();

  //! Toggle fullscreen playback
  void toggleFullscreen();

  //! Deletes a group from playlist
  void deleteItem();

  //! update parameters of regular overlay grid
  void updateGrid();

  void updateSelectedItems();

  //! Select a Stats Type and update GUI
  void setSelectedStats();

  //! Slot for updating the opacity of the current selected stats type (via items model)
  void updateStatsOpacity(int val);

  //! Slot for updating the grid visibility of the current selected stats type (via items model)
  void updateStatsGrid(bool val);
    
  void showAbout();

  void openProjectWebsite();

  void saveScreenshot();

  void updateSettings();
  
  void handleKeyPress(QKeyEvent* key);

  void checkNewVersion();

  // Show the open file dialog
  void showFileOpenDialog();

private slots:
  //! Timeout function for playback timer
  //void newFrameTimeout();

  void openRecentFile();
  
protected:

  virtual void keyPressEvent( QKeyEvent * event );

private:
  
  /// Return the primary and secondary playlist item that is currently selected
  playlistItem* selectedPrimaryPlaylistItem();
  playlistItem* selectedSecondaryPlaylistItem();

  /// Get the width/height for the current frameSize selection (in frameSizeComboBox)
  void convertFrameSizeComboBoxIndexToSize(int *width, int*height);
  
  SettingsWindow p_settingswindow;

  void createMenusAndActions();
  void updateRecentFileActions();

  // variables related to alternative window mode (YUV Checker)
  QMainWindow p_inspectorWindow;
  QMainWindow p_playlistWindow;


  QAction* openYUVFileAction;
  QAction* savePlaylistAction;
  QAction* addTextAction;
  QAction* addDifferenceAction;
  QAction* saveScreenshotAction;
  QAction* showSettingsAction;
  QAction* deleteItemAction;

  QAction* zoomToStandardAction;
  QAction* zoomToFitAction;
  QAction* zoomInAction;
  QAction* zoomOutAction;

  QAction* togglePlaylistAction;
  QAction* toggleStatisticsAction;
  QAction* toggleDisplayOptionsAction;
  QAction* toggleFileInfoAction;
  QAction* togglePropertiesAction;
  QAction* toggleControlsAction;
  QAction* toggleFullscreenAction;
  QAction* enableSingleWindowModeAction;
  QAction* enableSeparateWindowModeAction;

  QAction* playPauseAction;
  QAction* nextItemAction;
  QAction* previousItemAction;
  QAction* nextFrameAction;
  QAction* previousFrameAction;

  QAction *aboutAction;
  QAction *bugReportAction;
  QAction *featureRequestAction;
  QAction *checkNewVersionAction;

  QAction *recentFileActs[MAX_RECENT_FILES];

  QString strippedName(const QString &fullFileName);
};

#endif // MAINWINDOW_H
