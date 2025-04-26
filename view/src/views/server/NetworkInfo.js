import React from "react";
import ExpandedForm from "./../ExpandedForm";
import AddressItem from "./AddressItem";

export const NetworkInfo = ({ data, onOpenAddressWorker}) => {
  const { ip, mac, name, netmask, addresses } = data;

  return (
    <ExpandedForm title={name + ": кількість знайдених адресів  (" + addresses.length + ")"}>
        <div>
          <div><strong>Інтерфейс:</strong> {name}</div>
          <div><strong>IP:</strong> {ip}</div>
          <div><strong>MAC:</strong> {mac}</div>
          <div><strong>Маска:</strong> {netmask}</div>
          <div><strong>Знайдені адреси ({addresses.length})</strong></div>
        </div>

        {addresses.length ?
          <div>
            <ul>
              {addresses.map((addr, i) => (
                <AddressItem
                  key={i}
                  address={addr}
                  isHost={addr === ip}
                  onOpenAddressWorker={onOpenAddressWorker}
                />
              ))}
            </ul>
          </div>
          :
          null
        }
    </ExpandedForm>
  );
};

export default NetworkInfo;