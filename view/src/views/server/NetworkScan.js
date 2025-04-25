import React, { useState, useEffect } from "react";
import ExpandedForm from "./../ExpandedForm";
import NetworkInfoList from "./NetworkInfoList";

export const NetworkScan = ({ sendMessage, lastResponse }) => {
  const [isScanning, setIsScanning] = useState(false);

  const handleScan = () => {
    setIsScanning(true);
    sendMessage({ command: "get_scan" });
  };

  useEffect(() => {
    if (lastResponse && Array.isArray(lastResponse)) {
      setIsScanning(false);
    }
  }, [lastResponse]);

  const onConfigure = (ip) => {
    console.log("!onConfigure" + ip)
  }

  const onTop = (ip) => {
    console.log("!onTop" + ip)
  }

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
      {!isScanning && lastResponse && Array.isArray(lastResponse) && lastResponse.length > 0 && (
        <ExpandedForm title="Результат сканування:">
          <NetworkInfoList items={lastResponse} onConfigure={onConfigure} onTop={onTop} />
        </ExpandedForm>
      )}
    </ExpandedForm>
  );
};
export default NetworkScan;
