/***************************************************************************
    keychainbridge.h
    -------------------
    begin                : Nov 21, 2016
    copyright            : (C) 2016 Boundless Spatial Inc.
    author               : Alessandro Pasotti
    email                : apasotti@boundlessgeo.com

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KeyChainBridge_H
#define KeyChainBridge_H

//QT4 includes
#include <QObject>

//QGIS includes
#include "../qgisplugin.h"

//forward declarations
class QAction;
class QToolBar;

class QgisInterface;
class QgsAuthManager;

/**
* \class Plugin
* \brief [name] plugin for QGIS
* [description]
*/
class KeyChainBridge: public QObject, public QgisPlugin
{
    Q_OBJECT
  public:

    //////////////////////////////////////////////////////////////////////
    //
    //                MANDATORY PLUGIN METHODS FOLLOW
    //
    //////////////////////////////////////////////////////////////////////

    /**
    * Constructor for a plugin. The QgisInterface pointer is passed by
    * QGIS when it attempts to instantiate the plugin.
    * @param theInterface Pointer to the QgisInterface object.
     */
    KeyChainBridge( QgisInterface * theInterface );
    //! Destructor
    virtual ~KeyChainBridge();

  public slots:
    //! init the gui
    virtual void initGui();
    //! Show the dialog box
    void run();
    //! unload the plugin
    void unload();
    //! show the help document
    void help();

  private slots:

    /**
    * Called when a password has been verify (or not)
    * @param verified The state of password's verification
    */
   void masterPasswordVerified( bool verified );

   //! Connected to the authmanager signal
   void requestCredentials( const QString&, QString *, QString *, const QString&, bool * );

   //! Connected to the authmanager signal
   void requestCredentialsMasterPassword( QString *password, bool stored, bool *ok );

   //! Capture the master password from the credentials dialog
   void credentialsDialogAccepted();

   //! Delete master password from wallet
   void on_deleteMasterPassword_triggered();

   //! Save master password in the wallet
   void on_saveMasterPassword_triggered();

   //! Toggle plugin functions ( saved in the settings )
   void on_useWallet_changed();

   //! Toggle plugin logging ( saved in the settings )
   void on_loggingEnabled_changed();

  protected:

   bool eventFilter(QObject *obj, QEvent *event);

  private:

   //! Print a debug message in QGIS
   void debug(QString msg);

   //! Read settings
   void readSettings();

   //! Write settings
   void writeSettings();

   //! Plugin is enabled and authmanager too
   bool pluginIsEnabled();

   //! Ask the user if he wants to store the master password
   void askSaveMasterPassword(QString message);

   //! Cached master password getter
   QString masterPassword() { return mMasterPassword; }

   //! Check if password is the same as in auth manager
   //! This method will only return something meaningful if the auth manager password is set
   //! (check it with QgsAuthManager::instance()->masterPasswordIsSet())
   bool passwordIsSame(QString password);

   //! Read Master password from the wallet
   QString readMasterPassword();

   //! Delete master password from wallet
   bool deleteMasterPassword();

   //! Store Master password in the wallet
   bool storeMasterPassword(QString password);

   //! Error message setter
   void setErrorMessage(QString errorMessage) { mErrorMessage = errorMessage; }

   //! Error message getter
   QString errorMessage() { return mErrorMessage; }

   //! Dirty flag setter
   void setIsDirty( bool dirty ) { mIsDirty = dirty; }

   //! Dirty flag getter
   bool isDirty( ) { return mIsDirty; }

   //! Ask the user, and then store
   void saveMasterPassword();

   //! Show an error to the user
   void showError();

   //! Show an info to the user
   void showInfo(QString message);

    ////////////////////////////////////////////////////////////////////
    //
    // MANDATORY PLUGIN PROPERTY DECLARATIONS  .....
    //
    ////////////////////////////////////////////////////////////////////

    int mPluginType;
    //! Pointer to the QGIS interface object
    QgisInterface *mQGisIface;
    //!pointer to the qaction for this plugin
    QAction * mQActionPointer;

    ////////////////////////////////////////////////////////////////////
    //
    // ADD YOUR OWN PROPERTY DECLARATIONS AFTER THIS POINT.....
    //
    ////////////////////////////////////////////////////////////////////

    //! The user has chosen of using this plugin to store and retrieve the master pwd from his wallet
    bool mUseWallet;

    //! The cached master password
    QString mMasterPassword;

    //! Master password verification has failed
    bool mVerificationError;

    //! Store last error message
    QString mErrorMessage;

    //! Master password in memory is not in sync with the wallet
    //! This could be for several reasons: error in reading, empty password, wrong password etc.
    bool mIsDirty;

    //! Store auth manager instance
    QgsAuthManager* mAuthManager;

    QAction* mUseWalletAction;

    QAction* mLoggingEnabledAction;

    //! Enable logging
    bool mLoggingEnabled;

    //! Master password name in the wallets
    static const QLatin1String sMasterPasswordName;

    //! Wallet folder in the wallets
    static const QLatin1String sWalletFolderName;
};

#endif //KeyChainBridge_H
