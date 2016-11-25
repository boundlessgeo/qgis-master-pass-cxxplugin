# KeyChain Authmanager Bridge

This plugin enables storage and synchronization of the master password with
an external wallet.

It is based on the cross-platform [QtKeychain library](https://github.com/frankosterfeld/qtkeychain).

From the library README:

QtKeychain is a Qt API to store passwords and other secret data securely. How the data is stored depends on the platform:

 * **Mac OS X:** Passwords are stored in the OS X Keychain.

 * **Linux/Unix:** If running, GNOME Keyring is used, otherwise qtkeychain tries to use KWallet (via D-Bus), if available.

 * **Windows:** By default, the Windows Credential Store is used (requires Windows 7 or newer).
Pass -DUSE_CREDENTIAL_STORE=OFF to cmake use disable it. If disabled, QtKeychain uses the Windows API function
[CryptProtectData](http://msdn.microsoft.com/en-us/library/windows/desktop/aa380261%28v=vs.85%29.aspx "CryptProtectData function")
to encrypt the password with the user's logon credentials. The encrypted data is then persisted via QSettings.

In unsupported environments QtKeychain will report an error. It will not store any data unencrypted unless explicitly requested (setInsecureFallback( true )).

## Worflow

The wallet is used by default by the plugin but can be disabled through a menu
item.

The plugin will try to retrieve the password from the wallet and keep it in
sync automatically, but in a few cases it cannot detect a master password change
ant it will need the user to enter the master password again in order to capture
and store it.

If the plugin is installed when the master password has already been entered by
the user, it will prompt the user to store the password in the wallet.

In any case the plugin detects that the password is not synced (like in the case of
a password reset), it will prompt the user to store the password in the wallet
and the user will need to enter the password again.

If the password stored in the walled is no longer valid, the new password will
be stored automatically when the user enters it in the standard credentials
dialog.