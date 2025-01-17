/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file ChainOperationsParams.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2015
 */

#pragma once

#include <libdevcore/Common.h>
#include <libethcore/Precompiled.h>

#include "Common.h"
#include "EVMSchedule.h"

namespace dev
{
namespace eth
{

class PrecompiledContract
{
public:
	PrecompiledContract() = default;
	PrecompiledContract(
		PrecompiledPricer const& _cost,
		PrecompiledExecutor const& _exec,
		u256 const& _startingBlock = 0
	):
		m_cost(_cost),
		m_execute(_exec),
		m_startingBlock(_startingBlock)
	{}
	PrecompiledContract(
		unsigned _base,
		unsigned _word,
		PrecompiledExecutor const& _exec,
		u256 const& _startingBlock = 0
	);

	bigint cost(bytesConstRef _in) const { return m_cost(_in); }
	std::pair<bool, bytes> execute(bytesConstRef _in) const { return m_execute(_in); }

	u256 const& startingBlock() const { return m_startingBlock; }

private:
	PrecompiledPricer m_cost;
	PrecompiledExecutor m_execute;
	u256 m_startingBlock = 0;
};

struct ChainOperationParams
{
	ChainOperationParams();

	explicit operator bool() const { return accountStartNonce != Invalid256; }

	/// The chain sealer name: e.g. Ethash, NoProof, BasicAuthority
	std::string sealEngineName = "NoProof";

	/// General chain params.
private:
public:
	EVMSchedule const& scheduleForBlockNumber(u256 const& _blockNumber) const;
	u256 maximumExtraDataSize = 1024;
	u256 accountStartNonce = 0;
	bool tieBreakingGas = true;
	u256 minGasLimit;
	u256 maxGasLimit;
	u256 gasLimitBoundDivisor;
	u256 homesteadForkBlock;
	u256 EIP150ForkBlock;
	u256 EIP158ForkBlock;
	u256 byzantiumForkBlock;
	u256 constantinopleForkBlock;
	u256 daoHardforkBlock;
    //int chainID = 0; // Distinguishes different chains (mainnet, Ropsten, etc). --> Removed, change datadir name to distinguish
	int networkID = 0; // Distinguishes different sub protocols.

	u256 minimumDifficulty;
	u256 difficultyBoundDivisor;
	u256 durationLimit;
    u256 targetBlockInterval = 9;
    u256 initialSupply, inflationFactorPerBlockFemtoPercent;
	bool allowFutureBlocks = false;
	u256 registrar;

	/// Precompiled contracts as specified in the chain params.
	std::unordered_map<Address, PrecompiledContract> precompiled;
};

}
}
