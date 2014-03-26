using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEditor
{
    interface IParsable<T>
    {
        T Parse(String input);
        String ToExportFormat();
    }
}
