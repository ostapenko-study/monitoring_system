import React from "react";
import ConfigAgentView from './ConfigAgentView'
import ConfigAgentEditor from './ConfigAgentEditor'
import AgentTopManager from "./AgentTopManager";

const AgentConfigation = ({ sendMessage, lastResponse, source_key, config }) => {
  const handleSendMessage = (data) => {
    sendMessage({
      data: data,
      to: source_key,
      index: data.index
    });
  };

  return (
    <div>
        <AgentTopManager lastResponse={lastResponse} sendMessage={handleSendMessage}/>
        <ConfigAgentView config={config}/>
        <ConfigAgentEditor config={config} onSave={(new_config) => console.log(new_config)}/>
    </div>
  );
};

export default AgentConfigation;
