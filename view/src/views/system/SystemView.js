
import ExpandedForm from '../ExpandedForm';

import CpuView from '../CpuView'
import SystemMemView from './SystemMemView'

export const SystemView = ({data, totals}) => {
  return (
    <div>
        <ExpandedForm title="ЦПУ">
          <CpuView data={data.cpu} totalCpu={totals.cpu}/>
        </ExpandedForm>
        
        <ExpandedForm title="ОП">
          <SystemMemView data={data.memory} totalMemory={totals.memory} totalSwap={totals.swap}/>
        </ExpandedForm>
    </div>
  );
};

export default SystemView;