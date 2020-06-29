// Copyright (c) 2014-2015 The Bitcoin Core developers
// Copyright (c) 2019 Bitcoin Association
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef BITCOIN_CHAINPARAMSBASE_H
#define BITCOIN_CHAINPARAMSBASE_H

#include <memory>
#include <string>

/**
 * CBaseChainParams defines the base parameters
 * (shared between bitcoin-cli and bitcoind)
 * of a given instance of the Bitcoin system.
 */
class CBaseChainParams
{
public:
    /** BIP70 chain name strings (main, test or regtest) */
    static const std::string MAIN;
    static const std::string TESTNET;
    static const std::string REGTEST;
    static const std::string STN;

    CBaseChainParams(int port, const std::string& data_dir);

    const std::string& DataDir() const { return strDataDir; }
    int RPCPort() const { return nRPCPort; }

private:
    int nRPCPort;
    std::string strDataDir;
};

/**
 * Creates and returns a std::unique_ptr<CBaseChainParams> of the chosen chain.
 * @returns a CBaseChainParams* of the chosen chain.
 * @throws a std::runtime_error if the chain is not supported.
 */
std::unique_ptr<CBaseChainParams>
CreateBaseChainParams(const std::string &chain);

/**
 * Append the help messages for the chainparams options to the
 * parameter string.
 */
void AppendParamsHelpMessages(std::string &strUsage, bool debugHelp = true);

/**
 * Return the currently selected parameters. This won't change after app
 * startup, except for unit tests.
 */
const CBaseChainParams &BaseParams();

/** Sets the params returned by Params() to those for the given network. */
void SelectBaseParams(const std::string &chain);

/**
 * Looks for -regtest, -testnet and returns the appropriate BIP70 chain name.
 * @return CBaseChainParams::MAX_NETWORK_TYPES if an invalid combination is
 * given. CBaseChainParams::MAIN by default.
 */
std::string ChainNameFromCommandLine();

#endif // BITCOIN_CHAINPARAMSBASE_H