/***************************************************************************
 *   Copyright (C) 2016 by Boundless Spatial                               *
 *   apasotti@boundlessgeo.com                                             *
 *                                                                         *
 *   This is a plugin generated from the QGIS plugin template              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef KeyChainBridgeGUI_H
#define KeyChainBridgeGUI_H

#include <QDialog>
#include <ui_keychainbridgeguibase.h>

/**
@author Tim Sutton
*/
class KeyChainBridgeGui : public QDialog, private Ui::KeyChainBridgeGuiBase
{
    Q_OBJECT
  public:
    KeyChainBridgeGui( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~KeyChainBridgeGui();

  private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_buttonBox_helpRequested();

};

#endif
