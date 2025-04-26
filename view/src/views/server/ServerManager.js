import React, { useState, useCallback, useEffect } from 'react';
import NetworkScan from './NetworkScan';
import ExpandedForm from './../ExpandedForm';

export const ServerManager = ({ sendMessage , lastResponse}) => {

  return (
      <ExpandedForm title={"Команди для сервера"}>
        <NetworkScan sendMessage={sendMessage} lastResponse={lastResponse} />
      </ExpandedForm>
  );
};

export default ServerManager;
