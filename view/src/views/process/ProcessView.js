import ExpandedForm from '../ExpandedForm';
import ProcessMemView from './ProcessMemView'
import CpuView from '../CpuView'

export const ProcessView = ({data, totals}) => {

  const title_str = `PID: ${data.pid} ; PPID: ${data.ppid}; name: ${data.name}`;

  return (
    <ExpandedForm title={title_str}>
      <ExpandedForm title="CPU">
        <CpuView data={data.cpu} totalCpu={totals.cpu}/>
      </ExpandedForm>
      <ExpandedForm title="Memory">
        <ProcessMemView data={data.memory} totalMemory={totals.memory} totalSwap={totals.swap}/>
      </ExpandedForm>
    </ExpandedForm>
  );
};

export default ProcessView;