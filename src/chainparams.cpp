// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0x87;
        pchMessageStart[3] = 0xa6;
        vAlertPubKey = ParseHex("04a36564b96a4756bc6b132a04b94baafeac5d5257fe028e80695c62f7c2f81f85d251a216df3be197653f454852a2d08c6314aad5ca3cbe5616262ca3e7a6feef");
        nDefaultPort = 30031;
        nRPCPort = 30033;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Bitcoin Exchange BTCC Halts Fiat And Crypto Lending, by: JP Buntinx - January 13, 2017"; // Fri, 13 Jan 2017 03:35:17 GMT
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1484278517, vin, vout, 0); // Fri, 13 Jan 2017 03:35:17 GMT
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1484278517; // Fri, 13 Jan 2017 03:35:17 GMT
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1015460;

        /** Genesis Block MainNet */
        /*
Hashed MainNet Genesis Block Output
block.hashMerkleRoot == fb5c1cb95b2452f7d5b5c6837812349d681e073af9440438a32305ffed14518c
block.nTime = 1484278517
block.nNonce = 1015460
block.GetHash = 000009382cda8c797a597f8d08cbfbaae134d34bc072c4e3a1b0fa68f5ca660e

        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000009382cda8c797a597f8d08cbfbaae134d34bc072c4e3a1b0fa68f5ca660e"));
        assert(genesis.hashMerkleRoot == uint256("0xfb5c1cb95b2452f7d5b5c6837812349d681e073af9440438a32305ffed14518c"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,48);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,53);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("Seed01",  "199.26.184.214"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 240; // Initially ~220 Sec during PoW
        if(nBestHeight > nLastPoWBlock) // Scaled down for PoS only phase
        {
          nTargetSpacing = 240;
        }
        if(nBestHeight > nStartPoSBlock) // Scaled up for PoW/PoS twin phase
        {
          if(nBestHeight <= nLastPoWBlock)
          {
            nTargetSpacing = 720;
          }
        }
        nTargetTimespan = 10 * nTargetSpacing;
        nLastPoWBlock = 440005; // 224840000 total PoW coins mined 447340000 overall in supply
        nStartPoSBlock = 5000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x11;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0xef;
        pchMessageStart[3] = 0xae;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("03b47584b96e9056bc6b132a04b94baafeac5d5257fe028e80695c62f7c2f81f85d251a216df3af197653f454852a2d08c6314aad5ca3cbe5616262ca3e7a6faac");
        nDefaultPort = 30026;
        nRPCPort = 30028;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 28000;

        /** Genesis Block TestNet */
        /*
block.hashMerkleRoot == fb5c1cb95b2452f7d5b5c6837812349d681e073af9440438a32305ffed14518c
block.nTime = 1484278517
block.nNonce = 28000
block.GetHash = 00008937cc00a2a00ad8f4a2be7ac30fb54a3335443f82e6f4c976128b18f686
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00008937cc00a2a00ad8f4a2be7ac30fb54a3335443f82e6f4c976128b18f686"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,29);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,56);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 200;
        nLastPoWBlock = 0x7fffffff;
        nStartPoSBlock = 4500;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0x98;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1484279517;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 39003;
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
Hashed RegNet Genesis Block Output
block.hashMerkleRoot == fb5c1cb95b2452f7d5b5c6837812349d681e073af9440438a32305ffed14518c
block.nTime = 1484279517
block.nNonce = 8
block.GetHash = 02718c13e34c3a6e985f3282beae84bb9a2bdfc311376ac068c15b106c2151b1
        */

        assert(hashGenesisBlock == uint256("0x02718c13e34c3a6e985f3282beae84bb9a2bdfc311376ac068c15b106c2151b1"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
