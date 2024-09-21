import { ENS } from 'web3-eth-ens';

//const ens = new ENS(undefined,'https://mainnet.infura.io/v3/6894bcee642b497d8d9d7b0e52df192d');
const ens = new ENS(undefined,'https://sepolia.infura.io/v3/6894bcee642b497d8d9d7b0e52df192d');

console.log(await ens.getText('quantum.eth','myquantumkey'));



