import React, { useState, useCallback, useEffect } from 'react';
import NetworkScan from './NetworkScan';
import ExpandedForm from './../ExpandedForm';

export const ServerManager = ({ sendMessage , lastResponse}) => {
  
  const [scanData, setScanData]  = useState([])


  useEffect(() => {
    if(lastResponse.command === "get_scan"){
        setScanData(lastResponse.interfaces)
    }
  }, [lastResponse]);

  return (
      <ExpandedForm title={"Server commands"}>
        <NetworkScan sendMessage={sendMessage} lastResponse={scanData} />
      </ExpandedForm>
  );
};

export default ServerManager;
