import React, { useState, useEffect } from "react";
import ExpandedForm from "./../ExpandedForm";
import NetworkInfoList from "./NetworkInfoList";

import AddressWorkerModal from "./AddressWorkerModal";

export const NetworkScan = ({ sendMessage, lastResponse }) => {
  const [isScanning, setIsScanning] = useState(false);
  const [scanData, setScanData] = useState([]);


  const [showAddressWorkerModal, setAddressWorkerModal] = useState(false);
  const [selectedIP, setSelectedIP] = useState(null);

  const handleScan = () => {
    setIsScanning(true);
    sendMessage({ command: "get_scan" });
  };

  useEffect(() => {
    if (lastResponse.command === "get_scan"){
      setIsScanning(false);
      setScanData(lastResponse.interfaces)
    }
  }, [lastResponse]);

  const handleOpenAddressWorker = (ip) => {
    setSelectedIP(ip);
    setAddressWorkerModal(true);
  };

  return (
    <ExpandedForm title="Сканування мережі">

      <div className="scan-button-wrapper">
        <button 
          onClick={handleScan} 
          disabled={isScanning}
          className="scan-button"  
        >
          {isScanning ? "Сканування..." : "Сканувати мережу"}
        </button>
      </div>
      {!isScanning && scanData.length > 0 && (
        <ExpandedForm title="Результат сканування:">
          <NetworkInfoList items={scanData} onOpenAddressWorker={handleOpenAddressWorker}/>
        </ExpandedForm>
      )}

      {showAddressWorkerModal && (
        <AddressWorkerModal 
          ip={selectedIP} 
          sendMessage={sendMessage} 
          lastResponse={lastResponse} 
          onClose={() => setAddressWorkerModal(false)} 
        />
      )}

    </ExpandedForm>
  );
};
export default NetworkScan;
