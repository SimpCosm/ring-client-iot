/*
 *  Copyright (C) 2004-2017 Savoir-faire Linux Inc.
 *
 *  Author: Philippe Proulx <philippe.proulx@savoirfairelinux.com>
 *  Author: Houmin Wei <houmin.wei@pku.edu.cn>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "iotconfigurationmanager.h"
#include "configurationmanager_interface.h"

#include "media/audio/audiolayer.h"

IotConfigurationManager::IotConfigurationManager()
{}

auto
IotConfigurationManager::getAccountDetails(const std::string& accountID) -> decltype(DRing::getAccountDetails(accountID))
{
    return DRing::getAccountDetails(accountID);
}

auto
IotConfigurationManager::getVolatileAccountDetails(const std::string& accountID) -> decltype(DRing::getVolatileAccountDetails(accountID))
{
    return DRing::getVolatileAccountDetails(accountID);
}

void
IotConfigurationManager::setAccountDetails(const std::string& accountID, const std::map<std::string, std::string>& details)
{
    DRing::setAccountDetails(accountID, details);
}

auto
IotConfigurationManager::testAccountICEInitialization(const std::string& accountID) -> decltype(DRing::testAccountICEInitialization(accountID))
{
    return DRing::testAccountICEInitialization(accountID);
}


void
IotConfigurationManager::setAccountActive(const std::string& accountID, const bool& active)
{
    DRing::setAccountActive(accountID, active);
}

auto
IotConfigurationManager::getAccountTemplate(const std::string& accountType) -> decltype(DRing::getAccountTemplate(accountType))
{
    return DRing::getAccountTemplate(accountType);
}

auto
IotConfigurationManager::addAccount(const std::map<std::string, std::string>& details) -> decltype(DRing::addAccount(details))
{
    return DRing::addAccount(details);
}

auto
IotConfigurationManager::exportOnRing(const std::string& accountID, const std::string& password) -> decltype(DRing::exportOnRing(accountID, password))
{
    return DRing::exportOnRing(accountID, password);
}

auto
IotConfigurationManager::revokeDevice(const std::string& accountID, const std::string& password, const std::string& device) -> decltype(DRing::revokeDevice(accountID, password, device))
{
    return DRing::revokeDevice(accountID, password, device);
}

auto
IotConfigurationManager::getKnownRingDevices(const std::string& accountID) -> decltype(DRing::getKnownRingDevices(accountID))
{
    return DRing::getKnownRingDevices(accountID);
}

auto
IotConfigurationManager::lookupName(const std::string& account, const std::string& nameserver, const std::string& name) -> decltype(DRing::lookupName(account, nameserver, name))
{
    return DRing::lookupName(account, nameserver, name);
}

auto
IotConfigurationManager::lookupAddress(const std::string& account, const std::string& nameserver, const std::string& address) -> decltype(DRing::lookupAddress(account, nameserver, address))
{
    return DRing::lookupAddress(account, nameserver, address);
}

auto
IotConfigurationManager::registerName(const std::string& account, const std::string& password, const std::string& name) -> decltype(DRing::registerName(account, password, name))
{
    return DRing::registerName(account, password, name);
}

void
IotConfigurationManager::removeAccount(const std::string& accountID)
{
    DRing::removeAccount(accountID);
}

auto
IotConfigurationManager::getAccountList() -> decltype(DRing::getAccountList())
{
    return DRing::getAccountList();
}

void
IotConfigurationManager::sendRegister(const std::string& accountID, const bool& enable)
{
    DRing::sendRegister(accountID, enable);
}

void
IotConfigurationManager::registerAllAccounts(void)
{
    DRing::registerAllAccounts();
}

auto
IotConfigurationManager::sendTextMessage(const std::string& accountID, const std::string& to, const std::map<std::string, std::string>& payloads) -> decltype(DRing::sendAccountTextMessage(accountID, to, payloads))
{
    return DRing::sendAccountTextMessage(accountID, to, payloads);
}

auto
IotConfigurationManager::getMessageStatus(const uint64_t& id) -> decltype(DRing::getMessageStatus(id))
{
    return DRing::getMessageStatus(id);
}

auto
IotConfigurationManager::getTlsDefaultSettings() -> decltype(DRing::getTlsDefaultSettings())
{
    return DRing::getTlsDefaultSettings();
}

auto
IotConfigurationManager::getCodecList() -> decltype(DRing::getCodecList())
{
    return DRing::getCodecList();
}

auto
IotConfigurationManager::getSupportedTlsMethod() -> decltype(DRing::getSupportedTlsMethod())
{
    return DRing::getSupportedTlsMethod();
}

auto
IotConfigurationManager::getSupportedCiphers(const std::string& accountID) -> decltype(DRing::getSupportedCiphers(accountID))
{
    return DRing::getSupportedCiphers(accountID);
}

auto
IotConfigurationManager::getCodecDetails(const std::string& accountID, const unsigned& codecId) -> decltype(DRing::getCodecDetails(accountID, codecId))
{
    return DRing::getCodecDetails(accountID, codecId);
}

auto
IotConfigurationManager::setCodecDetails(const std::string& accountID, const unsigned& codecId, const std::map<std::string, std::string>& details)
-> decltype(DRing::setCodecDetails(accountID, codecId, details))
{
    return DRing::setCodecDetails(accountID, codecId, details);
}

auto
IotConfigurationManager::getActiveCodecList(const std::string& accountID) -> decltype(DRing::getActiveCodecList(accountID))
{
    return DRing::getActiveCodecList(accountID);
}

void
IotConfigurationManager::setActiveCodecList(const std::string& accountID, const std::vector<unsigned>& list)
{
    DRing::setActiveCodecList(accountID, list);
}

auto
IotConfigurationManager::getAudioPluginList() -> decltype(DRing::getAudioPluginList())
{
    return DRing::getAudioPluginList();
}

void
IotConfigurationManager::setAudioPlugin(const std::string& audioPlugin)
{
    DRing::setAudioPlugin(audioPlugin);
}

auto
IotConfigurationManager::getAudioOutputDeviceList() -> decltype(DRing::getAudioOutputDeviceList())
{
    return DRing::getAudioOutputDeviceList();
}

void
IotConfigurationManager::setAudioOutputDevice(const int32_t& index)
{
    DRing::setAudioOutputDevice(index);
}

void
IotConfigurationManager::setAudioInputDevice(const int32_t& index)
{
    DRing::setAudioInputDevice(index);
}

void
IotConfigurationManager::setAudioRingtoneDevice(const int32_t& index)
{
    DRing::setAudioRingtoneDevice(index);
}

auto
IotConfigurationManager::getAudioInputDeviceList() -> decltype(DRing::getAudioInputDeviceList())
{
    return DRing::getAudioInputDeviceList();
}

auto
IotConfigurationManager::getCurrentAudioDevicesIndex() -> decltype(DRing::getCurrentAudioDevicesIndex())
{
    return DRing::getCurrentAudioDevicesIndex();
}

auto
IotConfigurationManager::getAudioInputDeviceIndex(const std::string& name) -> decltype(DRing::getAudioInputDeviceIndex(name))
{
    return DRing::getAudioInputDeviceIndex(name);
}

auto
IotConfigurationManager::getAudioOutputDeviceIndex(const std::string& name) -> decltype(DRing::getAudioOutputDeviceIndex(name))
{
    return DRing::getAudioOutputDeviceIndex(name);
}

auto
IotConfigurationManager::getCurrentAudioOutputPlugin() -> decltype(DRing::getCurrentAudioOutputPlugin())
{
    return DRing::getCurrentAudioOutputPlugin();
}

auto
IotConfigurationManager::getNoiseSuppressState() -> decltype(DRing::getNoiseSuppressState())
{
    return DRing::getNoiseSuppressState();
}

void
IotConfigurationManager::setNoiseSuppressState(const bool& state)
{
    DRing::setNoiseSuppressState(state);
}

auto
IotConfigurationManager::isAgcEnabled() -> decltype(DRing::isAgcEnabled())
{
    return DRing::isAgcEnabled();
}

void
IotConfigurationManager::setAgcState(const bool& enabled)
{
    DRing::setAgcState(enabled);
}

void
IotConfigurationManager::muteDtmf(const bool& mute)
{
    DRing::muteDtmf(mute);
}

auto
IotConfigurationManager::isDtmfMuted() -> decltype(DRing::isDtmfMuted())
{
    return DRing::isDtmfMuted();
}

auto
IotConfigurationManager::isCaptureMuted() -> decltype(DRing::isCaptureMuted())
{
    return DRing::isCaptureMuted();
}

void
IotConfigurationManager::muteCapture(const bool& mute)
{
    DRing::muteCapture(mute);
}

auto
IotConfigurationManager::isPlaybackMuted() -> decltype(DRing::isPlaybackMuted())
{
    return DRing::isPlaybackMuted();
}

void
IotConfigurationManager::mutePlayback(const bool& mute)
{
    DRing::mutePlayback(mute);
}

auto
IotConfigurationManager::isRingtoneMuted() -> decltype(DRing::isRingtoneMuted())
{
    return DRing::isRingtoneMuted();
}

void
IotConfigurationManager::muteRingtone(const bool& mute)
{
    DRing::muteRingtone(mute);
}

auto
IotConfigurationManager::getAudioManager() -> decltype(DRing::getAudioManager())
{
    return DRing::getAudioManager();
}

auto
IotConfigurationManager::setAudioManager(const std::string& api) -> decltype(DRing::setAudioManager(api))
{
    return DRing::setAudioManager(api);
}

std::vector<std::string>
IotConfigurationManager::getSupportedAudioManagers()
{
    return {
#if HAVE_ALSA
        ALSA_API_STR,
#endif
#if HAVE_PULSE
        PULSEAUDIO_API_STR,
#endif
#if HAVE_JACK
        JACK_API_STR,
#endif
    };
}

auto
IotConfigurationManager::getRecordPath() -> decltype(DRing::getRecordPath())
{
    return DRing::getRecordPath();
}

void
IotConfigurationManager::setRecordPath(const std::string& recPath)
{
    DRing::setRecordPath(recPath);
}

auto
IotConfigurationManager::getIsAlwaysRecording() -> decltype(DRing::getIsAlwaysRecording())
{
    return DRing::getIsAlwaysRecording();
}

void
IotConfigurationManager::setIsAlwaysRecording(const bool& rec)
{
    DRing::setIsAlwaysRecording(rec);
}

void
IotConfigurationManager::setHistoryLimit(const int32_t& days)
{
    DRing::setHistoryLimit(days);
}

auto
IotConfigurationManager::getHistoryLimit() -> decltype(DRing::getHistoryLimit())
{
    return DRing::getHistoryLimit();
}

void
IotConfigurationManager::setAccountsOrder(const std::string& order)
{
    DRing::setAccountsOrder(order);
}

auto
IotConfigurationManager::getHookSettings() -> decltype(DRing::getHookSettings())
{
    return DRing::getHookSettings();
}

void
IotConfigurationManager::setHookSettings(const std::map<std::string, std::string>& settings)
{
    DRing::setHookSettings(settings);
}

auto
IotConfigurationManager::validateCertificate(const std::string& accountId, const std::string& certificate) -> decltype(DRing::validateCertificate(accountId, certificate))
{
   return DRing::validateCertificate(accountId, certificate);
}

auto
IotConfigurationManager::validateCertificatePath(const std::string& accountId, const std::string& certificate, const std::string& privateKey, const std::string& privateKeyPass, const std::string& caList) -> decltype(DRing::validateCertificatePath(accountId, certificate, privateKey, privateKeyPass, caList))
{
   return DRing::validateCertificatePath(accountId, certificate, privateKey, privateKeyPass, caList);
}

auto
IotConfigurationManager::getCertificateDetails(const std::string& certificate) -> decltype(DRing::getCertificateDetails(certificate))
{
    return DRing::getCertificateDetails(certificate);
}

auto
IotConfigurationManager::getCertificateDetailsPath(const std::string& certificate, const std::string& privateKey, const std::string& privateKeyPass) -> decltype(DRing::getCertificateDetailsPath(certificate, privateKey, privateKeyPass))
{
    return DRing::getCertificateDetailsPath(certificate, privateKey, privateKeyPass);
}

auto
IotConfigurationManager::getPinnedCertificates() -> decltype(DRing::getPinnedCertificates())
{
    return DRing::getPinnedCertificates();
}

auto
IotConfigurationManager::pinCertificate(const std::vector<uint8_t>& certificate, const bool& local) -> decltype(DRing::pinCertificate(certificate, local))
{
    return DRing::pinCertificate(certificate, local);
}

void
IotConfigurationManager::pinCertificatePath(const std::string& certPath)
{
    return DRing::pinCertificatePath(certPath);
}

auto
IotConfigurationManager::unpinCertificate(const std::string& certId) -> decltype(DRing::unpinCertificate(certId))
{
    return DRing::unpinCertificate(certId);
}

auto
IotConfigurationManager::unpinCertificatePath(const std::string& p) -> decltype(DRing::unpinCertificatePath(p))
{
    return DRing::unpinCertificatePath(p);
}

auto
IotConfigurationManager::pinRemoteCertificate(const std::string& accountId, const std::string& certId) -> decltype(DRing::pinRemoteCertificate(accountId, certId))
{
    return DRing::pinRemoteCertificate(accountId, certId);
}

auto
IotConfigurationManager::setCertificateStatus(const std::string& accountId, const std::string& certId, const std::string& status) -> decltype(DRing::setCertificateStatus(accountId, certId, status))
{
    return DRing::setCertificateStatus(accountId, certId, status);
}

auto
IotConfigurationManager::getCertificatesByStatus(const std::string& accountId, const std::string& status) -> decltype(DRing::getCertificatesByStatus(accountId, status))
{
    return DRing::getCertificatesByStatus(accountId, status);
}

auto
IotConfigurationManager::getTrustRequests(const std::string& accountId) -> decltype(DRing::getTrustRequests(accountId))
{
    return DRing::getTrustRequests(accountId);
}

auto
IotConfigurationManager::acceptTrustRequest(const std::string& accountId, const std::string& from) -> decltype(DRing::acceptTrustRequest(accountId, from))
{
    return DRing::acceptTrustRequest(accountId, from);
}

auto
IotConfigurationManager::discardTrustRequest(const std::string& accountId, const std::string& from) -> decltype(DRing::discardTrustRequest(accountId, from))
{
    return DRing::discardTrustRequest(accountId, from);
}

void
IotConfigurationManager::sendTrustRequest(const std::string& accountId, const std::string& to, const std::vector<uint8_t>& payload)
{
    DRing::sendTrustRequest(accountId, to, payload);
}

void
IotConfigurationManager::addContact(const std::string& accountId, const std::string& uri)
{
    DRing::addContact(accountId, uri);
}

void
IotConfigurationManager::removeContact(const std::string& accountId, const std::string& uri)
{
    DRing::removeContact(accountId, uri);
}

auto
IotConfigurationManager::getContactDetails(const std::string& accountId, const std::string& uri) -> decltype(DRing::getContactDetails(accountId, uri))
{
    return DRing::getContactDetails(accountId, uri);
}

auto
IotConfigurationManager::getContacts(const std::string& accountId) -> decltype(DRing::getContacts(accountId))
{
    return DRing::getContacts(accountId);
}

auto
IotConfigurationManager::getCredentials(const std::string& accountID) -> decltype(DRing::getCredentials(accountID))
{
    return DRing::getCredentials(accountID);
}

void
IotConfigurationManager::setCredentials(const std::string& accountID, const std::vector<std::map<std::string, std::string>>& details)
{
    DRing::setCredentials(accountID, details);
}

auto
IotConfigurationManager::getAddrFromInterfaceName(const std::string& interface) -> decltype(DRing::getAddrFromInterfaceName(interface))
{
    return DRing::getAddrFromInterfaceName(interface);
}

auto
IotConfigurationManager::getAllIpInterface() -> decltype(DRing::getAllIpInterface())
{
    return DRing::getAllIpInterface();
}

auto
IotConfigurationManager::getAllIpInterfaceByName() -> decltype(DRing::getAllIpInterfaceByName())
{
    return DRing::getAllIpInterfaceByName();
}

auto
IotConfigurationManager::getShortcuts() -> decltype(DRing::getShortcuts())
{
    return DRing::getShortcuts();
}

void
IotConfigurationManager::setShortcuts(const std::map<std::string, std::string> &shortcutsMap)
{
    DRing::setShortcuts(shortcutsMap);
}

void
IotConfigurationManager::setVolume(const std::string& device, const double& value)
{
    DRing::setVolume(device, value);
}

auto
IotConfigurationManager::getVolume(const std::string& device) -> decltype(DRing::getVolume(device))
{
    return DRing::getVolume(device);
}

auto
IotConfigurationManager::exportAccounts(const std::vector<std::string>& accountIDs, const std::string& filepath, const std::string& password) -> decltype(DRing::exportAccounts(accountIDs, filepath, password))
{
    return DRing::exportAccounts(accountIDs, filepath, password);
}

auto
IotConfigurationManager::importAccounts(const std::string& archivePath, const std::string& password) -> decltype(DRing::importAccounts(archivePath, password))
{
    return DRing::importAccounts(archivePath, password);
}

void
IotConfigurationManager::connectivityChanged()
{
    DRing::connectivityChanged();
}
